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

class EnemyGoap : public Entity {
private:
    State currentState;
    std::vector<std::shared_ptr<Action>> actions;

public:
    EnemyGoap(sf::Vector2i position, bool sight, bool range, bool health);
    void InitializeActions();
    void UpdateState(bool sight, bool range, bool health);
    void ExecuteAction();
    void update(float deltaTime, Grid& grid, sf::Vector2i playerPosition) override;
};

#endif