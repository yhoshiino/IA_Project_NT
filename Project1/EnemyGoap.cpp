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

void AttackAction::Execute(State& state, Grid& grid, Player& player, EnemyGoap& agent)  {
        cout << "Attacking player...\n";
}

void AttackAction::followPath(EnemyGoap& goap) {
    return;
}

FleeAction::FleeAction() {
    cost = 4;
}

bool FleeAction::CanExecute(const State& state)  {
    return state.lowHealth;
}

void FleeAction::Execute(State& state, Grid& grid, Player& player, EnemyGoap& agent) {
    cout << "Fleeing...\n";
}

void FleeAction::followPath(EnemyGoap& goap) {
    return;
}

FollowAction::FollowAction() {
    cost = 3;
}

bool FollowAction::CanExecute(const State& state)  {
    return state.playerInSight && !state.lowHealth;
}

void FollowAction::Execute(State& state, Grid& grid, Player& player, EnemyGoap& agent) {
    cout << "Following player...\n";
}

void FollowAction::followPath(EnemyGoap& goap) {
    return;
}

Clock clockE;
Time dt = clockE.restart();
float deltaTime = dt.asSeconds();

float PatrolAction::distance(Vector2f a, Vector2f b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

PatrolAction::PatrolAction() {
    cost = 4; // Patrol has the highest cost to be the default action
    currentWaypointIndex = 0;
    waypoints = {
    {3, 3},
    {6, 3},
    {6, 6},
    {3, 6}
    };
}

bool PatrolAction::CanExecute(const State& state)  {
    return !state.lowHealth && !state.playerInSight && !state.playerInRange;
}

void PatrolAction::Execute(State& state, Grid& grid, Player& player, EnemyGoap& agent) {
    if (path.empty()) {
        path = Pathfinding::findPath(grid, agent.position, sf::Vector2i(waypoints[currentWaypointIndex].x, waypoints[currentWaypointIndex].y));
        std::cout << "Path calculated." << endl;

        std::cout << currentWaypointIndex << endl;
    }

    followPath(agent);

    if (distance(sf::Vector2f(agent.position.x * 40, agent.position.y * 40), sf::Vector2f(waypoints[currentWaypointIndex].x * 40, waypoints[currentWaypointIndex].y * 40)) < 5.0f) {
        currentWaypointIndex = (currentWaypointIndex + 1) % waypoints.size();
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

void PatrolAction::followPath(EnemyGoap& goap) {
    deltaTime = clockE.restart().asSeconds();
    if (!path.empty()) {
        goap.position = sf::Vector2i(path.front().x, path.front().y);

        sf::Vector2f direction = sf::Vector2f(goap.position.x * 40, goap.position.y * 40) - goap.shape.getPosition();
        float dist = distance(goap.shape.getPosition(), sf::Vector2f(goap.position.x * CELL_SIZE, goap.position.y * CELL_SIZE));
        if (dist > 3.0f) { // Vérifier si on doit encore avancer vers le point
            direction /= dist; // Normaliser
            sf::Vector2f movement = direction * goap.Speed * deltaTime;
            goap.shape.move(movement); // Déplacer progressivement
            goap.position = sf::Vector2i(goap.shape.getPosition().x / 40, goap.shape.getPosition().y / 40); // Mettre à jour la grille
        }
        else {
            path.erase(path.begin()); // Supprimer le point atteint
        }
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
        bestAction->Execute(currentState, grid, player, *this);
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
    bool playerInSight = distanceChase(shape.getPosition(), player.shape.getPosition());
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
