//
// Created by yakir on 1/20/20.
//

#ifndef EX4_ASTAR_H
#define EX4_ASTAR_H

#include "Search.h"
#include "HeurCompare.h"


class AStar : public Search<Location*>{
private:
    queue<State<Location*>*> adjacent;
    priority_queue<State<Location*>*, vector<State<Location*>*>, HeurCompare> openQ;
    vector<State<Location*>*> closedQ;
public:
    string search(Isearchable<Location *> *searchable);
    bool isInOpenQ(State<Location*>* state);
    bool isInClosedQ(State<Location*>* state);
    void updateQ();
    double calcHeur(State<Location*>* state1, State<Location*>* state2);
    priority_queue<State<Location*>*, vector<State<Location*>*>, HeurCompare> copyQ();
};


#endif //EX4_ASTAR_H
