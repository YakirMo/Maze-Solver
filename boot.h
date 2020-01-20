//
// Created by yakir on 1/16/20.
//

#ifndef EX4_BOOT_H
#define EX4_BOOT_H

#include "server_side.h"
#include "CacheManager.h"
#include "ClientHandler.h"
#include "MyTestClientHandler.h"
#include "MySerialServer.h"
#include "StringReverser.h"
#include "FileCacheManager.h"

using namespace std;

namespace boot {
    class Main {
    public:
        void main(int port) {
            server_side::Server* server = new MySerialServer();
            Solver<string, string>* strSol = new StringReverser;
            CacheManager<string, string>* cache = new FileCacheManager<string, string>(50);
            ClientHandler *ch = new MyTestClientHandler(strSol, cache);
            server->open(port, ch);
        }
    };
}


#endif //EX4_BOOT_H
