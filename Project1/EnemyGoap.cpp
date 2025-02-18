#include "EnemyGoap.hpp"
#include "Planner.hpp"

EnemyGoap::EnemyGoap(sf::Vector2i position, bool sight, bool range, bool health)
    : Entity(position, sf::Color::Red, Speed), currentState(sight, range, health) {
    InitializeActions();
}

void EnemyGoap::InitializeActions() {
    actions.push_back(std::make_shared<PatrolAction>());
    actions.push_back(std::make_shared<FleeAction>());
    actions.push_back(std::make_shared<FollowAction>());
    actions.push_back(std::make_shared<AttackAction>());
}

void EnemyGoap::UpdateState(bool sight, bool range, bool health) {
    currentState.playerInSight = sight;
    currentState.playerInRange = range;
    currentState.lowHealth = health;
}

void EnemyGoap::ExecuteAction() {
    std::shared_ptr<Action> bestAction = Plan(currentState, actions);
    if (bestAction != nullptr) {
        bestAction->Execute(currentState);
    }
}

void EnemyGoap::update(float deltaTime, Grid& grid, sf::Vector2i playerPosition) {
    // Update the state based on some conditions (example logic)
    bool playerInSight = false/* logic to determine if the player is in sight */;
    bool playerInRange = false/* logic to determine if the player is in range */;
    bool lowHealth = false/* logic to determine if the enemy is low on health */;
    UpdateState(playerInSight, playerInRange, lowHealth);

    // Execute the best action for the current state
    ExecuteAction();

    //// Update the enemy position based on velocity
    //position += velocity * deltaTime;
    shape.setPosition(sf::Vector2f(position.x * 40, position.y * 40));
}