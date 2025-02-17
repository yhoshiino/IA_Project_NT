#pragma once
#ifndef STATE_H
#define STATE_H

#include <iostream>

class State {
public:
    bool playerInSight;
    bool playerInRange;
    bool lowHealth;

    State(bool sight, bool range, bool health)
        : playerInSight(sight), playerInRange(range), lowHealth(health) {
    }
};

#endif