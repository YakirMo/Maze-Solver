//
// Created by yakir on 1/20/20.
//

#include "AStar.h"

string AStar::search(Isearchable<Location *> *searchable) {
    int val = 0;
    queue<State<Location*>*> adjacent;
    priority_queue<State<Location*>*, vector<State<Location*>*>, HeurCompare> openQ;
    vector<State<Location*>*> closedQ;
    State<Location*>* state;
    State<Location*>* adjacentTo;
    openQ.emplace(searchable->getInitState());
    while (!openQ.empty()) {
        state = openQ.top();
        openQ.pop();
        closedQ.emplace_back(state);
        val += 1;
        if (state->equal(*(searchable->getGoal()))) {
            this->checkedNodes = val;
            return getBackTrack(searchable);
        }
        adjacent = searchable->getAllStates(state);
        while (!adjacent.empty()) {
            adjacentTo = adjacent.front();
            adjacent.pop();
            if ((!isInOpenQ(adjacentTo, openQ) && (!isInClosedQ(adjacentTo, closedQ)))) {
                adjacentTo->setLastState(state);
                adjacentTo->addCost(state->getPathCost());
                adjacentTo->setHeur(calcHeur(adjacentTo, searchable->getGoal()));
                openQ.emplace(adjacentTo);
                continue;
            } else if (isInClosedQ(adjacentTo, closedQ)) {
                continue;
            } else if (adjacentTo->getPathCost() > (state->getPathCost() + adjacentTo->getCost())) {
                adjacentTo->setLastState(state);
                adjacentTo->setPathCost(adjacentTo->getCost() + state->getPathCost());
                adjacentTo->setHeur(calcHeur(adjacentTo, searchable->getGoal()));
                updateQ(openQ);
            }
        }
    }
    return "Failed Solving";
}

bool AStar::isInOpenQ(State<Location *> *state,  priority_queue<State<Location*>*, vector<State<Location*>*>, HeurCompare> priorQ) {
    while (!priorQ.empty()) {
        if (state->equal(*(priorQ.top()))) {
            return true;
        }
        priorQ.pop();
    }
    return false;
}

bool AStar::isInClosedQ(State<Location *> *state, vector<State<Location*>*> closed) {
    int i;
    for (i = 0; i < closed.size(); i++) {
        if (state->equal(*(closed[i]))) {
            return true;
        }
    }
    return false;
}

priority_queue<State<Location*>*, vector<State<Location*>*>, HeurCompare> AStar::updateQ
        (priority_queue<State<Location*>*, vector<State<Location*>*>, HeurCompare> priorQ) {
priority_queue<State<Location*>*, vector<State<Location*>*>, HeurCompare> updatedQ;
    while (!priorQ.empty()) {
        updatedQ.emplace(priorQ.top());
        priorQ.pop();
    }
    return updatedQ;
}

double AStar::calcHeur(State<Location *> *state1, State<Location *> *state2) {
   double heur, pathCost, sum;
    pathCost = state1->getPathCost();
    heur = abs(state1->getCurrState()->location.first - state2->getCurrState()->location.first) +
           abs(state1->getCurrState()->location.second - state2->getCurrState()->location.second);
    sum = pathCost + heur;
    return sum;
}
