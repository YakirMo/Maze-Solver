//
// Created by yakir on 1/21/20.
//

#ifndef EX4_MYPARALLELSERVER_H
#define EX4_MYPARALLELSERVER_H


#include <netinet/in.h>
#include "server_side.h"
#include "Solver.h"
#include "CacheManager.h"
#include "SearcherObjectAdapter.h"
#include "AStar.h"
#include "BFS.h"
#include "DFS.h"
#include "BestFS.h"
#include "FileCacheManager.h"
#include "MyClientHandler.h"

class MyParallelServer : public server_side::Server{
public:
    int open(int port, ClientHandler *c);
    void start(int socketfd, sockaddr_in address, ClientHandler *c);
    void stop();
    bool shouldStop;
};

namespace bootPar {
    class MainPar {
    public:
        void mainPar(int port) {
            server_side::Server* serv = new MyParallelServer();
            Isearcher<Location*>* searcher = new AStar();
            Solver<Isearchable<Location*>*, string>* solver = new SearcherObjectAdapter<Location*>(searcher);
            CacheManager<string, string>* cache = new FileCacheManager<string, string>(50);
            ClientHandler* ch = new MyClientHandler(solver, cache);
            serv->open(port, ch);
        }
    };
}


#endif //EX4_MYPARALLELSERVER_H
