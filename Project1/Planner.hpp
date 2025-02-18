#pragma once
#ifndef PLANNER_HPP
#define PLANNER_HPP

#include <memory>
#include <vector>
#include "Action.hpp"

std::shared_ptr<Action> Plan(const State& currentState, const std::vector<std::shared_ptr<Action>>& actions);

#endif