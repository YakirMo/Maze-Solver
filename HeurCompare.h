//
// Created by yakir on 1/20/20.
//

#ifndef EX4_HEURCOMPARE_H
#define EX4_HEURCOMPARE_H


#include "State.h"
#include "Location.h"

class HeurCompare {
public:
    bool operator()(State<Location*>* state1, State<Location*>* state2) {
        return ((state1->getHeur()) > (state2->getHeur()));
    }
};


#endif //EX4_HEURCOMPARE_H
