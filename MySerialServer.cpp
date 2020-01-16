//
// Created by yakir on 1/14/20.
//

#include "iostream"
#include "MySerialServer.h"
#include "thread"


int MySerialServer::open(int port, ClientHandler &c) {
    int run;
    this->ch = c;
    this->shouldStop = false;
    this->port = port;
    this->socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socketfd == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        return -1;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(this->socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
        return -2;
    }
    ThreadsManager::getThread()->serverThread = thread(&MySerialServer::start, this);
    ThreadsManager::getThread()->serverThread.detach();
    return 0;
}

///Need to add timeout
int MySerialServer::start() {
    while (!shouldStop) {
        if (listen(this->socketfd, 5) == -1) {
            std::cerr << "Error during listening command" << std::endl;
            return -3;
        }
        cout << "Server is now listening..." << endl;
        // accept a client:
        client_socket = accept(this->socketfd, (struct sockaddr *) &address, (socklen_t *) &address);
        if (client_socket == -1) {
            std::cerr << "Error accepting client" << std::endl;
            return -4;
        }
        cout << "Server Connected" << endl;
        //solve given problem
        this->ch.HandleClient(this->socketfd);
    }
}

void MySerialServer::stop() {
    this->shouldStop = true;
}