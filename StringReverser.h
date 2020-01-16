//
// Created by yakir on 1/16/20.
//

#ifndef EX4_STRINGREVERSER_H
#define EX4_STRINGREVERSER_H

#include "Solver.h"
#include "string"

using namespace std;
//using stringReverser = Solver<string, string>;

class StringReverser : public Solver<string, string>{
     string Solve(string problem);
};


#endif //EX4_STRINGREVERSER_H
