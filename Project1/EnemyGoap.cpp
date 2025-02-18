#include "EnemyGoap.hpp"
#include "Planner.hpp"

EnemyGoap::EnemyGoap(Vector2i position, bool sight, bool range, bool health, float detectionRadius, float Health)
    : Entity(position, Color::Red), currentState(sight, range, health), detectionRadius(detectionRadius), health(Health) {
    InitializeActions();
}

void EnemyGoap::InitializeActions() {
    actions.push_back(make_shared<PatrolAction>());
    actions.push_back(make_shared<FleeAction>());
    actions.push_back(make_shared<FollowAction>());
    actions.push_back(make_shared<AttackAction>());
}

void EnemyGoap::UpdateState(bool sight, bool range, bool health) {
    currentState.playerInSight = sight;
    currentState.playerInRange = range;
    currentState.lowHealth = health;
}

void EnemyGoap::ExecuteAction() {
    shared_ptr<Action> bestAction = Plan(currentState, actions);
    if (bestAction != nullptr) {
        bestAction->Execute(currentState);
    }
}

bool EnemyGoap::distance(Vector2f a, Vector2f b) {
	float dist =sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
    if (dist <= detectionRadius) {
		return true;
    }
	return false;
}

float EnemyGoap::loseHealth() {
    health -= 1;
	return health;
}

bool EnemyGoap::Flee() {
    if (health <= 150) {
        return true;
    }
    return false;
}

void EnemyGoap::update(float deltaTime, Grid& grid, Vector2i playerPosition) {
    return;
}

void EnemyGoap::updateGoap(float deltaTime, Grid& grid,Player& player) {
    // Update the state based on some conditions (example logic)
    bool playerInSight = distance(shape.getPosition(), player.shape.getPosition());
    bool playerInRange = shape.getGlobalBounds().intersects(player.shape.getGlobalBounds());
    bool lowHealth = Flee();
    UpdateState(playerInSight, playerInRange, lowHealth);
    
    if (playerInRange==true) {
		loseHealth();
        cout << "Health: " << health << endl;
	}
    
    // Execute the best action for the current state
    ExecuteAction();

    //// Update the enemy position based on velocity
    //position += velocity * deltaTime;
    shape.setPosition(Vector2f(position.x * 40, position.y * 40));
}