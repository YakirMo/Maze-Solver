//
// Created by yakir on 1/17/20.
//

#ifndef EX4_ISEARCHER_H
#define EX4_ISEARCHER_H

#include "string"
#include "Isearchable.h"

using namespace std;

template <class S>
class Isearcher {
public:
    virtual string search(Isearchable<S>* problem) = 0;
};


#endif //EX4_ISEARCHER_H
