//
// Created by yakir on 1/19/20.
//

#ifndef EX4_MATMAZE_H
#define EX4_MATMAZE_H


#include "Isearchable.h"
#include "Location.h"
#include "vector"

using namespace std;

class MatMaze : public Isearchable<Location *> {
private:
    vector<vector<State<Location *> *>> matMaze;
    State<Location *> *startLoc;
    State<Location *> *endLoc;
    int cols;
    int rows;
public:
    MatMaze();
    ~MatMaze();
    MatMaze(vector<string> vec);
    bool goalState(State<Location*>* stat);
    State<Location*>* getGoal();
    State<Location*>* getInitState();
    string direction(State<Location*>* direct);
    queue<State<Location*>*> getAllStates(State<Location>* stat);
    State<Location*>* stringToState(string str);
};


#endif //EX4_MATMAZE_H
