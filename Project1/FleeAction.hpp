#ifndef FLEEACTION_H
#define FLEEACTION_H

#include "Action.hpp"

class FleeAction : public Action {
public:
    FleeAction() {
        cost = 4;
    }

    bool CanExecute(const State& state) override {
        return state.lowHealth;
    }

    void Execute(State& state) override {
        std::cout << "Fleeing...\n";
    }
};

#endif