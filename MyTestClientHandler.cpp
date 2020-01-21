//
// Created by yakir on 1/14/20.
//

#include <sys/socket.h>
#include "unistd.h"
#include "MyTestClientHandler.h"
#include "cstring"

using namespace std;


MyTestClientHandler::MyTestClientHandler(Solver<string, string> *s, CacheManager<string, string> *ch) {
    this->solver = s;
    this->cache = ch;
}

MyTestClientHandler::~MyTestClientHandler() {}

void MyTestClientHandler::HandleClient(int socket) {
    char buffer[1024] = {0};
    char* problem;
    string solution;
    int valread;
    //receives data from the client
    while (true) {
        valread = read(socket, buffer, 1024);
        while (buffer[0] == 0) {
            valread = read(socket, buffer, 1024);
        }
        problem = strtok(buffer, "\n");
        if (strcmp(problem, "end") == 0) {
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
    }
}