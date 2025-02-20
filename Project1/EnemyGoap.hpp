#pragma once
#ifndef ENEMYGOAP_HPP
#define ENEMYGOAP_HPP

#include <memory>
#include <vector>
#include <iostream>
#include "Entity.hpp"
#include "Player.hpp"
#include "Grid.hpp"

using namespace sf;
using namespace std;

class State {
public:
    bool playerInSight;
    bool playerInRange;
    bool lowHealth;

    State(bool sight, bool range, bool health)
        : playerInSight(sight), playerInRange(range), lowHealth(health) {
    }
};

class Action {
public:
    int cost;

    virtual bool CanExecute(const State& state) = 0;
    virtual void Execute(State& state, Grid& grid, EnemyGoap& enemy, Player& player) = 0;
    virtual void followPath() = 0;
    virtual ~Action() {}
};

class AttackAction : public Action {
public:
    AttackAction();

    bool CanExecute(const State& state) override;

    void Execute(State& state, Grid& grid, EnemyGoap& enemy, Player& player) override;
};

class FleeAction : public Action {
public:
    FleeAction();

    bool CanExecute(const State& state) override;

    void Execute(State& state, Grid& grid, EnemyGoap& enemy, Player& player) override;
};

class FollowAction : public Action {
public:
    FollowAction();

    bool CanExecute(const State& state) override;

    void Execute(State& state, Grid& grid, EnemyGoap& enemy, Player& player) override;
};

class PatrolAction : public Action {
public:
    class EnemyGoap;
    Clock clockE;
    Time dt = clockE.restart();
    float deltaTime = dt.asSeconds();

    float distance(sf::Vector2f a, sf::Vector2f b);

    PatrolAction();

    bool CanExecute(const State& state) override;

    void Execute(State& state, Grid& grid, EnemyGoap& enemy, Vector2i endPosition) override;

    void setPath(const std::vector<sf::Vector2i>& newPath) {
        path = newPath;
        updateWaypoints();
    }

    void updateWaypoints();
    
    float distance(Vector2f a, Vector2f b);

    void followPath();

private:
    std::vector<sf::Vector2i> path;
    std::vector<sf::Vector2f> waypoints;
    int currentWaypointIndex;
};

class Planner {
public:
    static std::shared_ptr<Action> Plan(const State& currentState, const std::vector<std::shared_ptr<Action>>& actions);
};
class EnemyGoap : public Entity {
private:
    State currentState;
    std::vector<std::shared_ptr<Action>> actions;
    float detectionRadius;
    float health;
public:
    EnemyGoap(sf::Vector2i position, bool sight, bool range, bool health, float detectionRadius, float Health);
    void InitializeActions();
    void UpdateState(bool sight, bool range, bool health);
    void ExecuteAction(Grid& grid, Player& player);
    void update(float deltaTime, Grid& grid, sf::Vector2i playerPosition) override;
    void updateGoap(float deltaTime, Grid& grid, Player& player);
    bool distanceChase(sf::Vector2f a, sf::Vector2f b);
    float loseHealth();
    bool Flee();
};

#endif