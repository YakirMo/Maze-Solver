//
// Created by yakir on 1/18/20.
//

#ifndef EX4_STATE_H
#define EX4_STATE_H

#include <cfloat>

template <class T>
class State {
private:
    double cost;
    double pathCost;
    T currState;
    State<T>* lastState;
    //For A*
    double heur;
public:

    State(T state, double costs) {
        this->currState = state;
        this->lastState = nullptr;
        this->cost = costs;
        this->pathCost = costs;
        this->heur = (FLT_MAX);
    }

    double getCost() {
        return this->cost;
    }

    double getPathCost() {
        return this->pathCost;
    }

    bool equal (State<T> stat) {
        return this->currState->equals(stat.getCurrState());
    }

    T getCurrState() {
        return this->currState;
    };

    void addCost (double d) {
        this->pathCost = this->cost + d;
    }

    State<T>* getLastState() {
        return this->lastState;
    }

    double getHeur() {
        return this->heur;
    }

    void setHeur(double d) {
        this->heur = d;
    }

    void setPathCost(double d) {
        this->pathCost = d;
    }

    void setLastState(State<T>* stat) {
        this->lastState = stat;
    }

};

#endif //EX4_STATE_H
