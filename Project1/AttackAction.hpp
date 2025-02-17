#ifndef ATTACKACTION_H
#define ATTACKACTION_H

#include "Action.hpp"

class AttackAction : public Action {
public:
    AttackAction() {
        cost = 2;
    }

    bool CanExecute(const State& state) override {
        return state.playerInSight && state.playerInRange && !state.lowHealth;
    }

    void Execute(State& state) override {
        std::cout << "Attacking player...\n";
    }
};

#endif