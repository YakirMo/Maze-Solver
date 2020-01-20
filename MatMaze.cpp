//
// Created by yakir on 1/19/20.
//

#include "MatMaze.h"

bool MatMaze::goalState(State<Location *> *stat) {
    return (stat->equal(*endLoc));
}

State<Location *> *MatMaze::getGoal() {
    return this->endLoc;
}

State<Location *> *MatMaze::getInitState() {
    return this->startLoc;
}

string MatMaze::direction(State<Location *> *direct) {
    string dir;
    State<Location *> *camefrom = direct->getLastState();
    double cameFromX = camefrom->getCurrState()->location.first;
    double cameFromY = camefrom->getCurrState()->location.second;
    double xLoc = direct->getCurrState()->location.first;
    double yLoc = direct->getCurrState()->location.second;
    if (cameFromX == (xLoc + 1)) {
        dir = "Up (" + to_string(direct->pathCost) + ")";
    } else if (cameFromX == (xLoc - 1)) {
        dir = "Down (" + to_string(direct->pathCost) + ")";
    } else if (cameFromY == (yLoc - 1)) {
        dir = "Right (" + to_string(direct->pathCost) + ")";
    } else if (cameFromY == (yLoc + 1)) {
        dir = "Left (" + to_string(direct->pathCost) + ")";
    }
    return dir;
}

queue<State<Location *> *> MatMaze::getAllStates(State<Location> *stat) {
    queue<State<Location *> *> allStates;
    double stateX = stat->getCurrState().location.first;
    double stateY = stat->getCurrState().location.second;
    // Up state
    if (stateX != 0) {
        if (this->matMaze[stateX - 1][stateY]->getCost() != -1) {
            allStates.push(this->matMaze[stateX - 1][stateY]);
        }
    }
    // Down state
    if (stateX != rows - 1) {
        if (this->matMaze[stateX + 1][stateY]->getCost() != -1) {
            allStates.push(this->matMaze[stateX + 1][stateY]);
        }
    }
    // Left state
    if (stateY != 0) {
        if (this->matMaze[stateX][stateY - 1]->getCost() != -1) {
            allStates.push(this->matMaze[stateX][stateY - 1]);
        }
    }
    // Right state
    if (stateY != cols - 1) {
        if (this->matMaze[stateX][stateY + 1]->getCost() != -1) {
            allStates.push(this->matMaze[stateX][stateY + 1]);
        }
    }
    return allStates;
}

State<Location *> *MatMaze::stringToState(string str) {
    int i;
    string helper;
    string xLoc;
    string yLoc;
    for (i = 0; i < str.length(); i++) {
        if (str[i] == ',') {
            xLoc = helper;
            helper.clear();
        } else if (str[i] == ' ') {
            helper.append(1, str[i]);
        }
    }
    yLoc = helper;
    double x = stoi(xLoc);
    double y = stoi(yLoc);
    return matMaze[x][y];
}

MatMaze::MatMaze(vector<string> vec) {
    int i, j, colss = 0, vecSize = (vec.size() - 2);
    double cost;
    string helper;
    vector<State<Location *> *> singleRow;
    this->rows = (vecSize);
    for (i = 0; i < vecSize; i++) {
        for (j = 0; j < vec[i].length(); j++) {
            if (vec[i][j] == ',') {
                cost = stod(helper);
                helper.clear();
                auto *state = new State<Location *>(new Location(i, colss), cost);
                state->setPathCost(DBL_MAX);
                singleRow.emplace_back(state);
                colss += 1;
            } else if (vec[i][j] != ' ') {
                helper.append(1, vec[i][j]);
            }
        }
        cost = stod(helper);
        helper.clear();
        auto state2 = new State<Location*>(new Location(i, colss), cost);
        singleRow.emplace_back(state2);
        this->matMaze.emplace_back(singleRow);
        singleRow.clear();
        this->cols = colss +1;
        colss = 0;
    }
}
