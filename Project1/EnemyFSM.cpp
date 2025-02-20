#include "EnemyFSM.hpp"
#include <cmath>

EnemyFSM::EnemyFSM(sf::Vector2i position, float detectionRange, float Speed) : Entity(position, sf::Color::Red, Speed), detectionRadius(detectionRange) {
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



float EnemyFSM::distance(sf::Vector2f a, sf::Vector2f b) {
    return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
}
