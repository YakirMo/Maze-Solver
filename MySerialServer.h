//
// Created by yakir on 1/14/20.
//

#ifndef EX4_MYSERIALSERVER_H
#define EX4_MYSERIALSERVER_H

#include "server_side.h"

class MySerialServer: public server_side::Server {
private:
    int socket;

public:
    void open(int port, ClientHandler c);
    void stop();
};


#endif //EX4_MYSERIALSERVER_H
