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
        if (detectPlayer(sf::Vector2f(player.shape.getPosition().x * CELL_SIZE, player.shape.getPosition().y * CELL_SIZE))) {
            currentState = State::Chasing;
            path = Pathfinding::findPath(grid, sf::Vector2i(position.x, position.y) / 40, sf::Vector2i(player.shape.getPosition().x, player.shape.getPosition().y) / 40);
        }
        else {
            patrol(grid);
        }
        break;

    case State::Chasing:
        if (!detectPlayer(sf::Vector2f(player.shape.getPosition().x * CELL_SIZE, player.shape.getPosition().y * CELL_SIZE))) {
            currentState = State::Returning;
            path = Pathfinding::findPath(grid, sf::Vector2i(position.x, position.y) / 40, sf::Vector2i(waypoints[currentWaypointIndex].x, waypoints[currentWaypointIndex].y));
        }
        else {
            chase(sf::Vector2f(player.shape.getPosition().x * CELL_SIZE, player.shape.getPosition().y * CELL_SIZE), grid);
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

    if (distance(sf::Vector2f(position.x*40, position.y*40), sf::Vector2f(waypoints[currentWaypointIndex].x * 40, waypoints[currentWaypointIndex].y * 40)) < 5.0f) {
        currentWaypointIndex = (currentWaypointIndex + 1) % waypoints.size();
    }
}

void EnemyFSM::chase(sf::Vector2f playerPosition, Grid& grid) {
    std::cout << "Chasing player..." << endl;
    if (path.empty() || distance(sf::Vector2f(position.x * 40, position.y * 40), playerPosition) > 5.0f) {
        path = Pathfinding::findPath(grid, sf::Vector2i(position.x, position.y)/40, sf::Vector2i(playerPosition.x, playerPosition.y)/40);
    }
    followPath();
}

bool EnemyFSM::detectPlayer(sf::Vector2f playerPosition) {
    /*std::cout << "Detecting player..." << endl;*/
    return distance(shape.getPosition(), playerPosition) < detectionRadius;
 
    
}

void EnemyFSM::followPath() {
    if (!path.empty()) {
        position = sf::Vector2i(path.front().x, path.front().y);
        shape.move(position.x * deltaTime * Speed, position.y * deltaTime * Speed);
        if (currentWaypointIndex == currentWaypointIndex+1) {
            path.erase(path.begin());
        }
    }
}

float EnemyFSM::distance(sf::Vector2f a, sf::Vector2f b) {
    return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
}
