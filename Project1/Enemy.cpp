#include "Enemy.hpp"
#include <cmath>

Enemy::Enemy(sf::Vector2f position) : Entity(position, sf::Color::Red) {
    currentState = State::Patrolling;
    currentWaypointIndex = 0;
    detectionRadius = 100.0f;
}

void Enemy::update(float deltaTime, Grid& grid, sf::Vector2f playerPosition) {
    switch (currentState) {
    case State::Patrolling:
        if (detectPlayer(playerPosition)) {
            currentState = State::Chasing;
            path = Pathfinding::findPath(grid, sf::Vector2i(position.x, position.y), sf::Vector2i(playerPosition.x, playerPosition.y));
        }
        else {
            patrol(grid);
        }
        break;

    case State::Chasing:
        if (!detectPlayer(playerPosition)) {
            currentState = State::Returning;
            path = Pathfinding::findPath(grid, sf::Vector2i(position.x, position.y), sf::Vector2i(waypoints[currentWaypointIndex].x, waypoints[currentWaypointIndex].y));
        }
        else {
            chase(playerPosition, grid);
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

void Enemy::patrol(Grid& grid) {
    if (waypoints.empty()) return;

    if (path.empty()) {
        path = Pathfinding::findPath(grid, sf::Vector2i(position.x, position.y), sf::Vector2i(waypoints[currentWaypointIndex].x, waypoints[currentWaypointIndex].y));
    }

    followPath();

    if (distance(position, waypoints[currentWaypointIndex]) < 5.0f) {
        currentWaypointIndex = (currentWaypointIndex + 1) % waypoints.size();
        path.clear();
    }
}

void Enemy::chase(sf::Vector2f playerPosition, Grid& grid) {
    if (path.empty() || distance(position, playerPosition) > 5.0f) {
        path = Pathfinding::findPath(grid, sf::Vector2i(position.x, position.y), sf::Vector2i(playerPosition.x, playerPosition.y));
    }
    followPath();
}

bool Enemy::detectPlayer(sf::Vector2f playerPosition) {
    return distance(position, playerPosition) < detectionRadius;
}

void Enemy::followPath() {
    if (!path.empty()) {
        position = sf::Vector2f(path.front().x, path.front().y);
        path.erase(path.begin());
    }
}

float Enemy::distance(sf::Vector2f a, sf::Vector2f b) {
    return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
}
