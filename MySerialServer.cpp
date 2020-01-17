//
// Created by yakir on 1/14/20.
//

#include "iostream"
#include "MySerialServer.h"
#include "thread"


MySerialServer::MySerialServer() = default;

MySerialServer::~MySerialServer() {}

int MySerialServer::open(int port, ClientHandler *c) {
    this->shouldStop = false;
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        return -1;
    }
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
        return -2;
    }
    if (listen(socketfd, 5) == -1) {
        std::cerr << "Error during listening command" << std::endl;
        return -3;
    }
    cout << "Server is now listening..." << endl;
    ThreadsManager::getThread()->serverThread = thread(&MySerialServer::start, this, socketfd, address, c);
    ThreadsManager::getThread()->serverThread.join();
    cout << "done" << endl;
    close(socketfd);
    return 0;
}

///Need to add timeout
void MySerialServer::start(int socketfd, sockaddr_in address, ClientHandler *c) {
    while (!shouldStop) {
        // accept a client:
        int client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);
        timeval to;
        to.tv_sec = 10;
        setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &to, sizeof(to));
        if (client_socket == -1) {
            if (errno == EWOULDBLOCK || errno == EAGAIN) {
                cout << "No client connected - Timeout..." << endl;
                stop();
                break;
            }
            std::cerr << "Error accepting client" << std::endl;
            break;
        }

        cout << "Server Connected" << endl;
        //solve given problem
        c->HandleClient(client_socket);
    }
}

void MySerialServer::stop() {
    shouldStop = true;
}