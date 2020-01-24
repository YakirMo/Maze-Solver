//
// Created by yakir on 1/20/20.
//

#include "DFS.h"

string DFS::search(Isearchable<Location *> *searchable) {
    int val = 0;
    State<Location *> *currNode;
    State<Location *> *state;
    //vector<State<Location*>*> visitedNodes;
    stack<State<Location *> *> qU;
    qU.emplace(searchable->getInitState());
    while (!qU.empty()) {
        currNode = qU.top();
        qU.pop();
        val += 1;
        if (!alreadyVisited(currNode)) {
            this->visitedNodes.emplace_back(currNode);
        }
        if (currNode->equal(*searchable->getGoal())) {
            return getBackTrack(searchable);
        }
        queue<State<Location *> *> possibleMoves = searchable->getAllStates(currNode);
        while (!possibleMoves.empty()) {
            state = possibleMoves.front();
            possibleMoves.pop();
            if (!alreadyVisited(state)) {
                state->setLastState(currNode);
                state->setPathCost(currNode->getPathCost() + state->getCost());
                qU.emplace(state);
            }
        }
    }
    return "Failed Solving";
}

bool DFS::alreadyVisited(State<Location *> *state) {
    int i;
    for (i = 0; i < this->visitedNodes.size(); i++) {
        if (state->equal(*(this->visitedNodes[i]))) {
            return true;
        }
    }
    return false;
}

vector<State<Location *> *> DFS::getVisitedNodes() {
    return vector<State<Location *> *>();
}
