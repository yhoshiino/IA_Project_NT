#pragma once
#ifndef ENEMYGOAP_HPP
#define ENEMYGOAP_HPP

#include <memory>
#include <vector>
#include <iostream>
#include "Entity.hpp"
#include "Player.hpp"
#include "Grid.hpp"
#include "Pathfinding.hpp"

using namespace sf;
using namespace std;

class EnemyGoap;

class State {
public:
    bool playerInSight;
    bool playerInRange;
    bool lowHealth;

    State(bool sight, bool range, bool health);
};

class Action {
public:
    int cost;

    virtual bool CanExecute(const State& state) = 0;
    virtual void Execute(State& state, Grid& grid, Player& player, EnemyGoap& agent) = 0;
    virtual void followPath(EnemyGoap& goap) = 0;
    virtual ~Action() {}
};

class AttackAction : public Action {
public:
    AttackAction();

    bool CanExecute(const State& state) override;

    void Execute(State& state, Grid& grid, Player& player, EnemyGoap& agent) override;

    void followPath(EnemyGoap& goap) override;
};

class FleeAction : public Action {
public:
    FleeAction();

    bool CanExecute(const State& state) override;

    void Execute(State& state, Grid& grid, Player& player, EnemyGoap& agent) override;

    void followPath(EnemyGoap& goap) override;
};

class FollowAction : public Action {
public:
    FollowAction();

    bool CanExecute(const State& state) override;

    void Execute(State& state, Grid& grid, Player& player, EnemyGoap& agent) override;

    void followPath(EnemyGoap& goap) override;
};

class PatrolAction : public Action {
public:

    Clock clockE;
    Time dt = clockE.restart();
    float deltaTime = dt.asSeconds();

    float distance(sf::Vector2f a, sf::Vector2f b);

    PatrolAction();

    bool CanExecute(const State& state) override;

    void Execute(State& state, Grid& grid, Player& player, EnemyGoap& agent) override;

    void setPath(const std::vector<sf::Vector2i>& newPath);


    void updateWaypoints();

    void followPath(EnemyGoap& goap) override;

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