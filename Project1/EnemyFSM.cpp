#include "EnemyFSM.hpp"
#include <cmath>

EnemyFSM::EnemyFSM(sf::Vector2i position, float detectionRange, float Speed) : Entity(position, sf::Color::Red, Speed), detectionRadius(detectionRange), health(300) {
    currentState = State::Patrolling;
    currentWaypointIndex = 0;
    waypoints = {
    {3, 3},
    {6, 3},
    {6, 6},
    {3, 6}
    };
}

void EnemyFSM::update(float deltaTime, Grid& grid, sf::Vector2i playerPosition) {
    return;
}

void EnemyFSM::updateFSM(float deltaTime, Grid& grid, Player& player) {
    colision(player);
    if (health <= 150) {
        currentState = State::Fleeing;
    }
    switch (currentState) {
    case State::Patrolling:
        if (detectPlayer(sf::Vector2f(player.shape.getPosition().x, player.shape.getPosition().y))) {
            currentState = State::Chasing;
            path.clear();
        }
        else {
            patrol(grid);
        }
        break;

    case State::Chasing:
        if (!detectPlayer(sf::Vector2f(player.shape.getPosition().x, player.shape.getPosition().y))) {
            currentState = State::Returning;
            path = Pathfinding::findPath(grid, sf::Vector2i(position.x, position.y) / 40, sf::Vector2i(waypoints[currentWaypointIndex].x, waypoints[currentWaypointIndex].y));
        }
        else {
            chase(sf::Vector2f(player.shape.getPosition().x, player.shape.getPosition().y), grid);
        }
        break;

    case State::Returning:
        if (!path.empty()) {
            followPath();
        }
        else {
            currentState = State::Patrolling;
        }
        break;
    case State::Fleeing:
        flee(grid,player);
        break;
    }
}

void EnemyFSM::patrol(Grid& grid) {
    if (waypoints.empty()) return;

    if (path.empty()) {
        path = Pathfinding::findPath(grid, position, sf::Vector2i(waypoints[currentWaypointIndex].x, waypoints[currentWaypointIndex].y));
        std::cout << "Path calculated." << endl;

        std::cout << currentWaypointIndex << endl;
    }

    followPath();

    if (distance(sf::Vector2f(position.x * 40, position.y * 40), sf::Vector2f(waypoints[currentWaypointIndex].x * 40, waypoints[currentWaypointIndex].y * 40)) < 5.0f) {
        currentWaypointIndex = (currentWaypointIndex + 1) % waypoints.size();
    }
}

void EnemyFSM::chase(sf::Vector2f playerPosition, Grid& grid) {
    std::cout << "Chasing player..." << endl;
    if (path.empty()) {
        cout << "Path found" << endl;
        path = Pathfinding::findPath(grid, sf::Vector2i(position.x, position.y), sf::Vector2i(playerPosition.x / 40, playerPosition.y / 40));
        cout << path.size() << endl;
    }
    followPath();
}

bool EnemyFSM::detectPlayer(sf::Vector2f playerPosition) {
    return distance(shape.getPosition(), playerPosition) < detectionRadius;  
}

void EnemyFSM::followPath() {
    deltaTime = clockE.restart().asSeconds();
    if (!path.empty()) {
        position = sf::Vector2i(path.front().x, path.front().y);

        sf::Vector2f direction = sf::Vector2f(position.x * 40, position.y * 40) - shape.getPosition();
        float dist = distance(shape.getPosition(), sf::Vector2f(position.x * CELL_SIZE, position.y * CELL_SIZE));
        if (dist > 3.0f) { // Vérifier si on doit encore avancer vers le point
            direction /= dist; // Normaliser
            sf::Vector2f movement = direction * Speed * deltaTime;
            shape.move(movement); // Déplacer progressivement
            position = sf::Vector2i(shape.getPosition().x / 40, shape.getPosition().y / 40); // Mettre à jour la grille
        }
        else {
            path.erase(path.begin()); // Supprimer le point atteint
        }
    }
}

void EnemyFSM::colision(Player& player) {
    if (shape.getGlobalBounds().intersects(player.shape.getGlobalBounds())) {
        health -= 1;
    }
}

float EnemyFSM::distance(sf::Vector2f a, sf::Vector2f b) {
    return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
}

float length(Vector2f v) { return sqrt(v.x * v.x + v.y * v.y); }

void EnemyFSM::flee(Grid& grid, Player& player) {
    Vector2f direction = Vector2f(shape.getPosition().x - player.shape.getPosition().x, shape.getPosition().y - player.shape.getPosition().y);
    direction = Vector2f(direction.x / length(direction), direction.y / length(direction));
    velocity = direction * Speed * deltaTime;

    auto isWalkable = [&](float x, float y) {
        int gridX = static_cast<int>(x / CELL_SIZE);
        int gridY = static_cast<int>(y / CELL_SIZE);
        return gridX >= 0 && gridX < GRID_WIDTH && gridY >= 0 && gridY < GRID_HEIGHT && grid.getCell(gridX, gridY).walkable;
        };

    Vector2f newPosition = Vector2f(shape.getGlobalBounds().left, shape.getGlobalBounds().top) + direction;
    FloatRect newBounds(newPosition, shape.getSize());

    if (direction.x > 0)
    {
        if (isWalkable(newBounds.left + newBounds.width + 2, shape.getGlobalBounds().top) &&
            isWalkable(newBounds.left + newBounds.width + 2, shape.getGlobalBounds().top + shape.getGlobalBounds().height - 1))
        {
            shape.move(Vector2f(direction.x, 0));
        }
        else
        {
            cout << "obstacle" << endl;
        }
    }
    else
    {
        if (isWalkable(newBounds.left - 2, shape.getGlobalBounds().top) &&
            isWalkable(newBounds.left - 2, shape.getGlobalBounds().top + shape.getGlobalBounds().height - 1))
        {
            shape.move(Vector2f(direction.x, 0));
        }
        else
        {
            cout << "obstacle" << endl;
        }
    }

    if (direction.y > 0)
    {
        if (isWalkable(shape.getGlobalBounds().left, newBounds.top + newBounds.height + 2) &&
            isWalkable(shape.getGlobalBounds().left + shape.getGlobalBounds().width, newBounds.top + newBounds.height + 2))
        {
            shape.move(Vector2f(0, direction.y));
        }
    }
    else
    {
        if (isWalkable(shape.getGlobalBounds().left, newBounds.top - 2) &&
            isWalkable(shape.getGlobalBounds().left + shape.getGlobalBounds().width - 1, newBounds.top - 2))
        {
            shape.move(Vector2f(0, direction.y));
        }
    }
}