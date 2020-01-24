//
// Created by yakir on 1/16/20.
//

#ifndef EX4_THREADSMANAGER_H
#define EX4_THREADSMANAGER_H

#include "thread"
#include "queue"

using namespace std;

class ThreadsManager {
private:
    ThreadsManager() {};
    static ThreadsManager *aThread;
public:
    static ThreadsManager *getThread();
    thread serverThread;
    thread clientThread;
    queue<pthread_t> clients;
};


#endif //EX4_THREADSMANAGER_H
