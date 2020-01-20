//
// Created by yakir on 1/20/20.
//

#ifndef EX4_BFS_H
#define EX4_BFS_H


#include "Search.h"

class BFS : public Search<Location*> {
    string search(Isearchable<Location*> *searchable);
};


#endif //EX4_BFS_H
