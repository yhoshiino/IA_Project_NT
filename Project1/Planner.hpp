#ifndef PLANNER_H
#define PLANNER_H

#include <memory>
#include <vector>
#include "Action.hpp"

std::shared_ptr<Action> Plan(const State& currentState, const std::vector<std::shared_ptr<Action>>& actions) {
    std::shared_ptr<Action> bestAction = nullptr;
    int lowestCost = INT_MAX;

    for (const auto& action : actions) {
        if (action->CanExecute(currentState) && action->cost < lowestCost) {
            bestAction = action;
            lowestCost = action->cost;
        }
    }

    return bestAction;
}

#endif