#pragma once
#ifndef ENEMYGOAP_HPP
#define ENEMYGOAP_HPP

#include <memory>
#include <vector>
#include "State.hpp"
#include "Action.hpp"
#include "PatrolAction.hpp"
#include "FleeAction.hpp"
#include "FollowAction.hpp"
#include "AttackAction.hpp"
#include "Entity.hpp"
#include "Player.hpp"

class EnemyGoap : public Entity {
private:
    State currentState;
    std::vector<std::shared_ptr<Action>> actions;
    float detectionRadius;
    float health;
public:
    EnemyGoap(sf::Vector2i position, bool sight, bool range, bool health,float detectionRadius, float Health);
    void InitializeActions();
    void UpdateState(bool sight, bool range, bool health);
    void ExecuteAction();
    void update(float deltaTime, Grid& grid, sf::Vector2i playerPosition) override;
    void updateGoap(float deltaTime, Grid& grid, Player& player) ;
    bool distance(sf::Vector2f a, sf::Vector2f b);
    float loseHealth();
    bool Flee();

};

#endif