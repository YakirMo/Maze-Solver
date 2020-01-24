//
// Created by yakir on 1/20/20.
//

#ifndef EX4_ASTAR_H
#define EX4_ASTAR_H

#include "Search.h"
#include "HeurCompare.h"


class AStar : public Search<Location*>{
private:

public:
    string search(Isearchable<Location *> *searchable);
    bool isInOpenQ(State<Location*>* state,  priority_queue<State<Location*>*, vector<State<Location*>*>, HeurCompare> priorQ);
    bool isInClosedQ(State<Location*>* state,  vector<State<Location*>*> closed);
    priority_queue<State<Location*>*, vector<State<Location*>*>, HeurCompare> updateQ
    (priority_queue<State<Location*>*, vector<State<Location*>*>, HeurCompare> priorQ);
    double calcHeur(State<Location*>* state1, State<Location*>* state2);
};


#endif //EX4_ASTAR_H
