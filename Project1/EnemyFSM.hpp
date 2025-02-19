#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"
#include "Pathfinding.hpp"
#include "Grid.hpp"
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "Player.hpp"

class EnemyFSM : public Entity {
public:
    enum class State { Patrolling, Chasing, Returning };

    EnemyFSM(sf::Vector2i position, float detectionRange, float Speed);

    void update(float deltaTime, Grid& grid, sf::Vector2i playerPosition) override;

    void updateFSM(float deltaTime, Grid& grid, Player& player);

    Clock clockE;
    Time dt = clockE.restart();
    float deltaTime = dt.asSeconds();

private:
    State currentState;
    std::vector<sf::Vector2i> path;
    std::vector<sf::Vector2f> waypoints;
    int currentWaypointIndex;
    float detectionRadius;

    

    void patrol(Grid& grid);
    void chase(sf::Vector2f playerPosition, Grid& grid);
    bool detectPlayer(sf::Vector2f playerPosition);
    void followPath();
    float distance(sf::Vector2f a, sf::Vector2f b);
};

#endif // ENEMY_HPP
