//
// Created by yakir on 1/14/20.
//

#ifndef EX4_MYSERIALSERVER_H
#define EX4_MYSERIALSERVER_H

#include "server_side.h"
#include "unistd.h"
#include "netinet/in.h"
#include "MyTestClientHandler.h"
#include "ThreadsManager.h"

class MySerialServer: public server_side::Server {
private:
    int socketfd;
    int port;
    int client_socket;
    sockaddr_in address;
    bool shouldStop;
    ClientHandler* ch;
public:
    MySerialServer();
    ~MySerialServer();
    int open(int port, ClientHandler *c);
    int start();
    void stop();
};


#endif //EX4_MYSERIALSERVER_H
