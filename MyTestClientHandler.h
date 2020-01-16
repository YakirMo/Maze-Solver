//
// Created by yakir on 1/14/20.
//

#ifndef EX4_MYTESTCLIENTHANDLER_H
#define EX4_MYTESTCLIENTHANDLER_H

#include "CacheManager.h"
#include "ClientHandler.h"
#include "string"
#include "Solver.h"

template <class P, class S>
class MyTestClientHandler: public ClientHandler {
private:
    Solver<P, S>& solver;
    CacheManager<P, S> cache;
public:
    MyTestClientHandler(P, S);
    ~MyTestClientHandler();
    S HandleClient(int socket) override;
};


#endif //EX4_MYTESTCLIENTHANDLER_H
