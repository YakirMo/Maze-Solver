//
// Created by yakir on 1/18/20.
//

#ifndef EX4_COMPARE_H
#define EX4_COMPARE_H

#include "State.h"
#include "Location.h"

using namespace std;

class Compare {
public:
    bool operator()(State<Location*> *state1, State<Location*> *state2) {
        return state1->getPathCost() > state2->getPathCost();
    }
};

#endif //EX4_COMPARE_H
