//
// Created by yakir on 1/16/20.
//

#include "ThreadsManager.h"

ThreadsManager *ThreadsManager::aThread = 0;

//returns an instance of the threadsManager class, if it doesnt exist - creates one
ThreadsManager *ThreadsManager::getThread() {
    if (!aThread) {
        aThread = new ThreadsManager;
    }
    return aThread;
}