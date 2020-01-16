//
// Created by yakir on 1/14/20.
//

#include "unistd.h"
#include "MyTestClientHandler.h"
#include "FileCacheManager.h"
#include "string"

using namespace std;


template<class P, class S>
MyTestClientHandler<P, S>::MyTestClientHandler(P, S) {
    this->solver = new Solver<P, S>;
    this->cache = new FileCacheManager<P, S>(50);
}
//MyTestClientHandler<P, S>::~MyTestClientHandler() {}

template<class P, class S>
S MyTestClientHandler<P, S>::HandleClient(int socket) {
    char buffer[2048] = {0};
    P problem;
    S solution;
    //receives data from the client
    int valread = read(socket, buffer, 2048);
    problem = buffer;
    problem.erase(problem.find('\0'));
    if (problem.find("end")) {
        ///Might change
        return "0";
    }
    //Checks if there's a saved solution for the given problem
    if (this->cache.isThereSolution(problem)) {
        this->cache.getSolution(problem);
    } else {
      solution =  this->solver.solve(problem);
      this->cache.saveSolution(solution);
    }
    char cstr[solution.size() + 1];
    strcpy(cstr, solution.c_str());
    //sends the solution to the current client (which sent the problem)
    send(socket, cstr, strlen(cstr), 0);
    return solution;
    //close(socket); //closing the listening socket
}