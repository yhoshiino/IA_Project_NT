#include "EnemyGoap.hpp"
State::State(bool sight, bool range, bool health)
    : playerInSight(sight), playerInRange(range), lowHealth(health) {
}

AttackAction::AttackAction() {
    cost = 2;
}

bool AttackAction::CanExecute(const State& state)   {
    return state.playerInSight && state.playerInRange && !state.lowHealth;
}

void AttackAction::Execute(State& state, Grid& grid, EnemyGoap& enemy, Player& player)  {
        cout << "Attacking player...\n";
}

FleeAction::FleeAction() {
    cost = 4;
}

bool FleeAction::CanExecute(const State& state)  {
    return state.lowHealth;
}

void FleeAction::Execute(State& state, Grid& grid, EnemyGoap& enemy, Player& player)  {
    cout << "Fleeing...\n";
}

FollowAction::FollowAction() {
    cost = 3;
}

bool FollowAction::CanExecute(const State& state)  {
    return state.playerInSight && !state.lowHealth;
}

void FollowAction::Execute(State& state, Grid& grid, EnemyGoap& enemy, Player& player)  {
    cout << "Following player...\n";
}

Clock clockE;
Time dt = clockE.restart();
float deltaTime = dt.asSeconds();

float PatrolAction::distance(Vector2f a, Vector2f b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

PatrolAction::PatrolAction() {
    cost = 4; // Patrol has the highest cost to be the default action
}

bool PatrolAction::CanExecute(const State& state)  {
    return !state.lowHealth && !state.playerInSight && !state.playerInRange;
}

void PatrolAction::Execute(State& state, Grid& grid, EnemyGoap& enemy, Player& player) {
    if (currentWaypointIndex < waypoints.size()) {
        // Move towards the current waypoint
        Vector2f target = waypoints[currentWaypointIndex];
        Vector2f currentPos = enemy.shape.getPosition();
        float dx = target.x - currentPos.x;
        float dy = target.y - currentPos.y;
        float distance = sqrt(dx * dx + dy * dy);

        if (distance < 1.0f) {
            // Reached the current waypoint, move to the next one
            currentWaypointIndex++;
        }
        else {
            // Move towards the target
            enemy.shape.setPosition(currentPos.x + dx / distance, currentPos.y + dy / distance);
        }
    }
    else {
        // Completed the patrol path, reset to start again
        currentWaypointIndex = 0;
    }
}


void PatrolAction::updateWaypoints() {
    waypoints.clear();
    for (const auto& point : path) {
        waypoints.push_back(Vector2f(point.x * CELL_SIZE, point.y * CELL_SIZE));
    }
}

void PatrolAction::setPath(const vector<Vector2i>& newPath) {
    path = newPath;
    updateWaypoints();
}

void PatrolAction::followPath() {
    deltaTime = clockE.restart().asSeconds();
    if (!path.empty()) {
        enemy.shape.getposition() = Vector2i(path.front().x, path.front().y);

        Vector2f direction = Vector2f(position.x * 40, position.y * 40) - enemy.shape.getPosition();
        float dist = distance(shape.getPosition(), Vector2f(position.x * CELL_SIZE, position.y * CELL_SIZE));
        if (dist > 3.0f) { // Vérifier si on doit encore avancer vers le point
            direction /= dist; // Normaliser
            Vector2f movement = direction * Speed * deltaTime;
            shape.move(movement); // Déplacer progressivement
            position = Vector2i(shape.getPosition().x / 40, shape.getPosition().y / 40); // Mettre à jour la grille
        }
        else {
            path.erase(path.begin()); // Supprimer le point atteint
        }

        shape.setPosition(position.x * 40, position.y * 40);

        path.erase(path.begin());
    }
}

shared_ptr<Action> Planner::Plan(const State& currentState, const vector<shared_ptr<Action>>& actions) {
    shared_ptr<Action> bestAction = nullptr;
    int lowestCost = INT_MAX;
    for (const auto& action : actions) {
        if (action->CanExecute(currentState) && action->cost < lowestCost) {
            bestAction = action;
            lowestCost = action->cost;
        }
    }
    return bestAction;
}

EnemyGoap::EnemyGoap(Vector2i position, bool sight, bool range, bool health, float detectionRadius, float Health)
    : Entity(position, Color::Red, Speed), currentState(sight, range, health), detectionRadius(detectionRadius), health(Health) {
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

void EnemyGoap::ExecuteAction(Grid& grid, Player& player) {
    shared_ptr<Action> bestAction = Planner::Plan(currentState, actions);
    if (bestAction != nullptr) {
        bestAction->Execute(currentState, grid, *this, player);
    }
}

bool EnemyGoap::distanceChase(Vector2f a, Vector2f b) {
    float dist = sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
    return dist <= detectionRadius;
}

float EnemyGoap::loseHealth() {
    health -= 1;
    return health;
}

bool EnemyGoap::Flee() {
    return health <= 150;
}

void EnemyGoap::update(float deltaTime, Grid& grid, Vector2i playerPosition) {
    // Implement update logic if needed
}

void EnemyGoap::updateGoap(float deltaTime, Grid& grid, Player& player) {
    // Update the state based on some conditions (example logic)
    bool playerInSight = distance(shape.getPosition(), player.shape.getPosition());
    bool playerInRange = shape.getGlobalBounds().intersects(player.shape.getGlobalBounds());
    bool lowHealth = Flee();
    UpdateState(playerInSight, playerInRange, lowHealth);

    if (playerInRange) {
        loseHealth();
        cout << "Health: " << health << endl;
    }

    // Execute the best action for the current state
    ExecuteAction(grid, player);

    // Update the enemy position based on velocity
    shape.setPosition(Vector2f(position.x * 40, position.y * 40));
}
