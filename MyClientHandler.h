//
// Created by yakir on 1/19/20.
//

#ifndef EX4_MYCLIENTHANDLER_H
#define EX4_MYCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Isearchable.h"
#include "Location.h"
#include "Solver.h"
#include "CacheManager.h"


class MyClientHandler : public ClientHandler {
public:
    MyClientHandler(Solver<Isearchable<Location*>*, string>* solv, CacheManager<string, string>* cache);
    Solver<Isearchable<Location*>*, string>* solver;
    CacheManager<string, string>* cacheManager;
    void HandleClient(int socket);

};


#endif //EX4_MYCLIENTHANDLER_H
