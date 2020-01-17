//
// Created by yakir on 1/14/20.
//

#ifndef EX4_MYTESTCLIENTHANDLER_H
#define EX4_MYTESTCLIENTHANDLER_H

#include "CacheManager.h"
#include "ClientHandler.h"
#include "string"
#include "Solver.h"

class MyTestClientHandler: public ClientHandler {
private:
    Solver<string, string>* solver;
    CacheManager<string, string>* cache;
public:
    MyTestClientHandler(Solver<string, string>* s, CacheManager<string, string>* ch);
    ~MyTestClientHandler();
    void HandleClient(int socket) override;
};


#endif //EX4_MYTESTCLIENTHANDLER_H
