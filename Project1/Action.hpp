#pragma once
#ifndef ACTION_H
#define ACTION_H

#include "State.hpp"

class Action {
public:
    int cost;

    virtual bool CanExecute(const State& state) = 0;
    virtual void Execute(State& state) = 0;
    virtual ~Action() {}
};

#endif