#ifndef PATROLACTION_H
#define PATROLACTION_H

#include "Action.hpp"

class PatrolAction : public Action {
public:
    PatrolAction() {
        cost = 4; // Patrol has the highest cost to be the default action
    }

    bool CanExecute(const State& state) override {
        return !state.lowHealth && !state.playerInSight && !state.playerInRange;
    }

    void Execute(State& state) override {
        std::cout << "Patrolling...\n";
    }
};

#endif