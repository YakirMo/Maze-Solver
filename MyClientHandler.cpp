//
// Created by yakir on 1/19/20.
//

#include "MyClientHandler.h"

MyClientHandler::MyClientHandler(Solver<Isearchable<Location*>*, string>* solv, CacheManager<string, string>* cache) {
    this->solver = solv;
    this->cacheManager = cache;
}

void MyClientHandler::HandleClient(int socket) {}