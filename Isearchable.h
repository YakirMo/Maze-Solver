//
// Created by yakir on 1/17/20.
//

#ifndef EX4_ISEARCHABLE_H
#define EX4_ISEARCHABLE_H

#include "string"
#include "IState.h"
#include "queue"

using namespace std;

template <class P>
class Isearchable {
public:
    virtual bool goalState(IState<P>* stat) = 0;
    virtual IState<P> getGoal() = 0;
    virtual IState<P>* getInitState() = 0;
    virtual string direction(IState<P>* direct) = 0;
    virtual queue<IState<P>*> getAllStates(IState<P>* stat) = 0;

};

#endif //EX4_ISEARCHABLE_H
