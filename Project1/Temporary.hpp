//#include <iostream>
//
//class State {
//public:
//    bool playerInSight;
//    bool playerInRange;
//    bool lowHealth;
//
//    State(bool sight, bool range, bool health)
//        : playerInSight(sight), playerInRange(range), lowHealth(health) {
//    }
//};
//
//class Action {
//public:
//    int cost;
//
//    virtual bool CanExecute(const State& state) = 0;
//    virtual void Execute(State& state, Grid& grid, Vector2i enemyPosition, Vector2i endPosition) = 0;
//    virtual void followPath() = 0;
//    virtual ~Action() {}
//};
//
//class AttackAction : public Action {
//public:
//    AttackAction() {
//        cost = 2;
//    }
//
//    bool CanExecute(const State& state) override {
//        return state.playerInSight && state.playerInRange && !state.lowHealth;
//    }
//
//    void Execute(State& state, Grid& grid, Vector2i enemyPosition, Vector2i endPosition) override {
//        std::cout << "Attacking player...\n";
//    }
//};
//
//class FleeAction : public Action {
//public:
//    FleeAction() {
//        cost = 4;
//    }
//
//    bool CanExecute(const State& state) override {
//        return state.lowHealth;
//    }
//
//    void Execute(State& state, Grid& grid, Vector2i enemyPosition, Vector2i endPosition) override {
//        std::cout << "Fleeing...\n";
//    }
//};
//
//class FollowAction : public Action {
//public:
//    FollowAction() {
//        cost = 3;
//    }
//
//    bool CanExecute(const State& state) override {
//        return state.playerInSight && !state.lowHealth;
//    }
//
//    void Execute(State& state, Grid& grid, Vector2i enemyPosition, Vector2i endPosition) override {
//        std::cout << "Following player...\n";
//    }
//};
//
//class PatrolAction : public Action {
//public:
//
//    Clock clockE;
//    Time dt = clockE.restart();
//    float deltaTime = dt.asSeconds();
//
//    float distance(sf::Vector2f a, sf::Vector2f b) {
//        return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
//    }
//
//    PatrolAction() {
//        cost = 4; // Patrol has the highest cost to be the default action
//        currentWaypointIndex = 0;
//    }
//
//    bool CanExecute(const State& state) override {
//        return !state.lowHealth && !state.playerInSight && !state.playerInRange;
//    }
//
//    void Execute(State& state, Grid& grid, Vector2i enemyPosition, Vector2i endPosition) override {
//        if (currentWaypointIndex < waypoints.size()) {
//            // Move towards the current waypoint
//            sf::Vector2f target = waypoints[currentWaypointIndex];
//            sf::Vector2f currentPos = Vector2f(enemyPosition);
//            float dx = target.x - currentPos.x;
//            float dy = target.y - currentPos.y;
//            float distance = std::sqrt(dx * dx + dy * dy);
//
//            if (distance < 1.0f) {
//                // Reached the current waypoint, move to the next one
//                currentWaypointIndex++;
//            }
//            else {
//                // Move towards the target
//                enemy.shape.setPosition(currentPos.x + dx / distance, currentPos.y + dy / distance);
//            }
//        }
//        else {
//            // Completed the patrol path, reset to start again
//            currentWaypointIndex = 0;
//        }
//    }
//
//    void setPath(const std::vector<sf::Vector2i>& newPath) {
//        path = newPath;
//        updateWaypoints();
//    }
//
//    void updateWaypoints() {
//        waypoints.clear();
//        for (const auto& point : path) {
//            waypoints.push_back(sf::Vector2f(point.x * CELL_SIZE, point.y * CELL_SIZE));
//        }
//    }
//
//    void followPath() override {
//        deltaTime = clockE.restart().asSeconds();
//        if (!path.empty()) {
//            position = sf::Vector2i(path.front().x, path.front().y);
//
//            sf::Vector2f direction = sf::Vector2f(position.x * 40, position.y * 40) - shape.getPosition();
//            float dist = distance(shape.getPosition(), sf::Vector2f(position.x * CELL_SIZE, position.y * CELL_SIZE));
//            if (dist > 3.0f) { // Vérifier si on doit encore avancer vers le point
//                direction /= dist; // Normaliser
//                sf::Vector2f movement = direction * Speed * deltaTime;
//                shape.move(movement); // Déplacer progressivement
//                position = sf::Vector2i(shape.getPosition().x / 40, shape.getPosition().y / 40); // Mettre à jour la grille
//            }
//            else {
//                path.erase(path.begin()); // Supprimer le point atteint
//            }
//
//            / shape.setPosition(position.x 40, position.y * 40);
//
//            path.erase(path.begin()); */
//        }
//    }
//
//private:
//    std::vector<sf::Vector2i> path;
//    std::vector<sf::Vector2f> waypoints;
//    int currentWaypointIndex;
//};
//
//class Planner {
//public:
//    static std::shared_ptr<Action> Plan(const State& currentState, const std::vector<std::shared_ptr<Action>>& actions) {
//        std::shared_ptr<Action> bestAction = nullptr;
//        int lowestCost = INT_MAX;
//
//        for (const auto& action : actions) {
//            if (action->CanExecute(currentState) && action->cost < lowestCost) {
//                bestAction = action;
//                lowestCost = action->cost;
//            }
//        }
//
//        return bestAction;
//    }
//};