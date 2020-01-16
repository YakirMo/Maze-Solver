//
// Created by yakir on 1/14/20.
//

#ifndef EX4_SOLVER_H
#define EX4_SOLVER_H

using namespace std;


template <class P, class S>
class Solver {
    virtual S Solve(P problem) = 0;
};


#endif //EX4_SOLVER_H
