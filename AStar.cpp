//
// Created by yakir on 1/20/20.
//

#include "AStar.h"

string AStar::search(Isearchable<Location *> *searchable) {
    int val = 0;
    State<Location*>* state;
    State<Location*>* adjacentTo;
    this->openQ.emplace(searchable->getInitState());
    while (!this->openQ.empty()) {
        state = this->openQ.top();
        this->openQ.pop();
        this->closedQ.emplace_back(state);
        val += 1;
        if (state->equal(*(searchable->getGoal()))) {
            raiseCheckedNodes();
            return getBackTrack(searchable);
        }
        this->adjacent = searchable->getAllStates(state);
        while (!this->adjacent.empty()) {
            adjacentTo = this->adjacent.front();
            this->adjacent.pop();
            if ((!isInOpenQ(adjacentTo) && (!isInClosedQ(adjacentTo)))) {
                adjacentTo->setLastState(state);
                adjacentTo->addCost(state->getPathCost());
                adjacentTo->setHeur(calcHeur(adjacentTo, searchable->getGoal()));
                this->openQ.emplace(adjacentTo);
                continue;
            } else if (isInClosedQ(adjacentTo)) {
                continue;
            } else if (adjacentTo->getPathCost() > (state->getPathCost() + adjacentTo->getCost())) {
                adjacentTo->setLastState(state);
                adjacentTo->setPathCost(adjacentTo->getCost() + state->getPathCost());
                adjacentTo->setHeur(calcHeur(adjacentTo, searchable->getGoal()));
                updateQ();
            }
        }
    }
    return "Failed Solving";
}

bool AStar::isInOpenQ(State<Location *> *state) {
    priority_queue<State<Location*>*, vector<State<Location*>*>, HeurCompare> openQCopy (this->openQ);
    //openQCopy = this->openQ;
    while (!openQCopy.empty()) {
        if (state->equal(*(openQCopy.top()))) {
            return true;
        }
        openQCopy.pop();
    }
    return false;
}

bool AStar::isInClosedQ(State<Location *> *state) {
    int i;
    vector<State<Location*>*> closedQCopy (this->closedQ);
    //closedQCopy = this->closedQ;
    for (i = 0; i < closedQCopy.size(); i++) {
        if (state->equal(*(closedQCopy[i]))) {
            return true;
        }
    }
    return false;
}

void AStar::updateQ() {
    priority_queue<State<Location*>*, vector<State<Location*>*>, HeurCompare> openQCopy;
    while (!this->openQ.empty()) {
        openQCopy.emplace(this->openQ.top());
        this->openQ.pop();
    }
    this->openQ = openQCopy;
}

double AStar::calcHeur(State<Location *> *state1, State<Location *> *state2) {
   double heur, pathCost, sum;
    pathCost = state1->getPathCost();
    heur = abs(state1->getCurrState()->location.first - state2->getCurrState()->location.first) +
           abs(state1->getCurrState()->location.second - state2->getCurrState()->location.second);
    sum = pathCost + heur;
    return sum;
}

/*
priority_queue<State<Location *> *, vector<State<Location *> *>, HeurCompare> AStar::copyQ() {
    priority_queue<State<Location *> *, vector<State<Location *> *>, HeurCompare> copyQ;
    while (this->)
}
*/