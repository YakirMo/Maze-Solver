//
// Created by yakir on 1/14/20.
//

#ifndef EX4_CLIENTHANDLER_H
#define EX4_CLIENTHANDLER_H

#include "string"


using namespace std;

class ClientHandler {

public:
    virtual string HandleClient(int socket) = 0;
};


#endif //EX4_CLIENTHANDLER_H
