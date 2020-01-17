//
// Created by yakir on 1/14/20.
//

#include <sys/socket.h>
#include "unistd.h"
#include "MyTestClientHandler.h"
#include "FileCacheManager.h"
#include "cstring"

using namespace std;


MyTestClientHandler::MyTestClientHandler(Solver<string, string> *s, CacheManager<string, string> *ch) {
    this->solver = s;
    this->cache = ch;
}

MyTestClientHandler::~MyTestClientHandler() {}

void MyTestClientHandler::HandleClient(int socket) {
    char buffer[2048] = {0};
    string problem;
    string solution;
    int valread;
    //receives data from the client
    while (true) {
        valread = read(socket, buffer, 2048);
        problem = strtok(buffer, "\n");
        if (problem.find("end")) {
            return;
        }
        //Checks if there's a saved solution for the given problem
        if (this->cache->isThereSolution(problem)) {
            this->cache->getSolution(problem);
        } else {
            solution = this->solver->Solve(problem);
            this->cache->saveSolution(problem ,solution);
        }
        char cstr[solution.size() + 1];
        strcpy(cstr, solution.c_str());
        //sends the solution to the current client (which sent the problem)
        send(socket, cstr, strlen(cstr), 0);
        //close(socket); //closing the listening socket
    }
}