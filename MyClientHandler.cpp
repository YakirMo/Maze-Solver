//
// Created by yakir on 1/19/20.
//

#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
#include "MyClientHandler.h"
#include "mutex"
#include "MatMaze.h"
#include "cstring"

mutex mtx;

MyClientHandler::MyClientHandler(Solver<Isearchable<Location*>*, string>* solv, CacheManager<string, string>* cache) {
    this->solver = solv;
    this->cacheManager = cache;
}

void MyClientHandler::HandleClient(int socket) {
    mtx.lock();
    int i, sentMsg, valread;
    bool done = false;
    char buffer[4096] = {0};
    string oneRow, matMazeRow, sol;
    vector<string> vec;
    while (!done) {
        valread = read(socket, buffer, 4096);
        for (i =0; i < valread; i++) {
            if (oneRow == "end") {
                done = true;
                break;
            }
            if (buffer[i] == '\r' || buffer[i] == '\n') {
                if (buffer[i] == '\r') {
                    i++;
                }
                oneRow.append("\n");
                if (oneRow == "\n") {
                    oneRow.clear();
                    continue;
                }
                matMazeRow.append(oneRow);
                vec.emplace_back(oneRow);
                oneRow.clear();
            } else {
                oneRow.append(1, buffer[i]);
            }
        }
        if (oneRow == "end") {
            done = true;
        }
    }
    if (this->cacheManager->isThereSolution(matMazeRow)) {
        sol = this->cacheManager->getSolution(matMazeRow);
    } else {
        Isearchable<Location*>* matMaze = new MatMaze(vec);
        sol = this->solver->Solve(matMaze);
        this->cacheManager->saveSolution(matMazeRow, sol);
    }
    char cstr[sol.size() + 1];
    strcpy(cstr, sol.c_str());
    //sends the solution to the current client (which sent the problem)
   sentMsg = send(socket, cstr, strlen(cstr), 0);
   if (sentMsg == -1) {
       cout << "Couldn't send solution";
   }
    mtx.unlock();
}