//
// Created by yakir on 1/20/20.
//

#include "BestFS.h"
#include "unordered_set"

string BestFS::search(Isearchable<Location *> *searchable) {
    int val = 0;
    State<Location*>* state;
    State<Location*>* popped;
    unordered_set<State<Location*>*> closedQ;
    addToQ(searchable->getInitState());
    while (QSize() > 0) {
        popped = popQ();
        closedQ.emplace(popped);
        val += 1;
        if (popped->equal(*(searchable->getGoal()))) {
            return getBackTrack(searchable);
        }
        queue<State<Location*>*> possibleMoves = searchable->getAllStates(popped);
        while (!possibleMoves.empty()) {
            state = possibleMoves.front();
            possibleMoves.pop();
            if (closedQ.find(state) == closedQ.end() && (!inQ(state))) {
                state->setPathCost(popped->getPathCost() + state->getCost());
                state->setLastState(popped);
                addToQ(state);
            } else if (state->getPathCost() > (popped->getPathCost() + state->getCost())) {
                state->setPathCost(popped->getPathCost() + state->getCost());
                state->setLastState(popped);
                if (!inQ(state)) {
                    addToQ(state);
                } else {
                    updateQ(state);
                }
            }
        }
    }
    return "Failed Solving";
}