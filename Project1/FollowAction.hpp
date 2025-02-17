#ifndef FOLLOWACTION_H
#define FOLLOWACTION_H

#include "Action.hpp"

class FollowAction : public Action {
public:
    FollowAction() {
        cost = 3;
    }

    bool CanExecute(const State& state) override {
        return state.playerInSight && !state.lowHealth;
    }

    void Execute(State& state) override {
        std::cout << "Following player...\n";
    }
};

#endif