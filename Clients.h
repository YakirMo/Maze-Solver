//
// Created by yakir on 1/21/20.
//

#ifndef EX4_CLIENTS_H
#define EX4_CLIENTS_H

#include "ClientHandler.h"

class Clients {
public:
    int socket;
    ClientHandler *ch;
    Clients(int soc, ClientHandler *c) {
        this->socket = soc;
        this->ch = c;
    }
};


#endif //EX4_CLIENTS_H
