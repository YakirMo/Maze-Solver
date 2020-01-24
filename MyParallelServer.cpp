//
// Created by yakir on 1/21/20.
//

#include "iostream"
#include "unistd.h"
#include "MyParallelServer.h"
#include "Clients.h"
#include "ThreadsManager.h"

using namespace std;

int MyParallelServer::open(int port, ClientHandler *c) {
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
    start(socketfd, address, c);
    cout << "done" << endl;
    close(socketfd);
    return 0;
}

void *threadClient(void *client) {
    auto cl = (Clients*) client;
    cl->ch->HandleClient(cl->socket);
}

void MyParallelServer::start(int socketfd, sockaddr_in address, ClientHandler *c) {
    shouldStop = false;
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
        setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &to, sizeof(to));
        auto cl = new Clients(client_socket, c);
        pthread_t pthread;
        if(pthread_create(&pthread, nullptr, threadClient, cl) < 0 ) {
            cout << "Error threading a client" << endl;
            exit(1);
        }
        ThreadsManager::getThread()->clients.emplace();
    }
    close(socketfd);
}

void MyParallelServer::stop() {
    shouldStop = true;
    while (!ThreadsManager::getThread()->clients.empty()) {
        pthread_join(ThreadsManager::getThread()->clients.front(), nullptr);
        ThreadsManager::getThread()->clients.pop();
    }
}
