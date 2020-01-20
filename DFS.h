//
// Created by yakir on 1/20/20.
//

#ifndef EX4_DFS_H
#define EX4_DFS_H

#include "Search.h"


class DFS : public Search<Location*> {
private:
    vector<State<Location*>*> visitedNodes;
public:
    string search(Isearchable<Location*> *searchable);
    bool alreadyVisited(State<Location*>* state);
    vector<State<Location*>*> getVisitedNodes();
};


#endif //EX4_DFS_H
