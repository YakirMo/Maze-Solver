//
// Created by yakir on 1/17/20.
//

#ifndef EX4_ISEARCHABLE_H
#define EX4_ISEARCHABLE_H

#include "string"
#include "State.h"
#include "queue"

using namespace std;

template <class P>
class Isearchable {
public:
    virtual bool goalState(State<P>* stat) = 0;
    virtual State<P>* getGoal() = 0;
    virtual State<P>* getInitState() = 0;
    virtual string direction(State<P>* direct) = 0;
    virtual queue<IState<P>*> getAllStates(State<P>* stat) = 0;

};

#endif //EX4_ISEARCHABLE_H
