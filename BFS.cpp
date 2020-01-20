//
// Created by yakir on 1/20/20.
//

#include "set"
#include "BFS.h"


string BFS::search(Isearchable<Location *> *searchable) {
    int val = 0;
    set<State<Location *> *> setBfs;
    set<State<Location *> *>::iterator iter;
    State<Location *> *state;
    State<Location *> *popped;
    addToQ(searchable->getInitState());
    setBfs.emplace(searchable->getInitState());
    while (QSize() != 0) {
        popped = popQ();
        val += 1;
        if (popped->equal(*(searchable->getGoal()))) {
            return getBackTrack(searchable);
        }
        queue<State<Location *> *> possibleMoves = searchable->getAllStates(popped);
        while (!possibleMoves.empty()) {
            state = possibleMoves.front();
            possibleMoves.pop();
            iter = setBfs.find(state);
            if (iter == setBfs.end()) {
                state->setLastState(popped);
                state->setPathCost(popped->getPathCost() + 1);
                setBfs.emplace(state);
                addToQ(state);
            }
        }
    }
    return "Failed Solving";
}