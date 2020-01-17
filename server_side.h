//
// Created by yakir on 1/14/20.
//

#ifndef EX4_SERVER_SIDE_H
#define EX4_SERVER_SIDE_H

#include "ClientHandler.h"

namespace server_side {
    class Server {
    public:
       virtual int open(int port, ClientHandler *ch) = 0;
       virtual void stop() = 0;

    };
}

#endif //EX4_SERVER_SIDE_H
