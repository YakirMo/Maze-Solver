//
// Created by yakir on 1/20/20.
//

#ifndef EX4_BESTFS_H
#define EX4_BESTFS_H


#include "Search.h"

class BestFS : public Search<Location*>{
    string search(Isearchable<Location*>* searchable);
};


#endif //EX4_BESTFS_H
