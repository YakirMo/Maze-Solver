//
// Created by yakir on 1/20/20.
//

#include "DFS.h"

string DFS::search(Isearchable<Location *> *searchable) {
    int val = 0;
    State<Location *> *currNode;
    State<Location *> *state;
    vector<State<Location*>*> visitedNodes;
    stack<State<Location *> *> vertexStack;
    vertexStack.emplace(searchable->getInitState());
    while (!vertexStack.empty()) {
        currNode = vertexStack.top();
        vertexStack.pop();
        val += 1;
        if (!alreadyVisited(currNode, visitedNodes)) {
            visitedNodes.emplace_back(currNode);
        }
        if (currNode->equal(*searchable->getGoal())) {
            this->checkedNodes = val;
            return getBackTrack(searchable);
        }
        queue<State<Location *> *> possibleMoves = searchable->getAllStates(currNode);
        while (!possibleMoves.empty()) {
            state = possibleMoves.front();
            possibleMoves.pop();
            if (!alreadyVisited(state, visitedNodes)) {
                state->setLastState(currNode);
                state->setPathCost(currNode->getPathCost() + state->getCost());
                vertexStack.emplace(state);
            }
        }
    }
    return "Failed Solving";
}

bool DFS::alreadyVisited(State<Location *> *checkedState, vector<State<Location*>*> visitedNodes) {
    for (auto state :visitedNodes) {
        if (checkedState->equal(*(state))) {
            return true;
        }
    }
    return false;
}

