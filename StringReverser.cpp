//
// Created by yakir on 1/16/20.
//

#include "StringReverser.h"
#include <bits/stdc++.h>

string StringReverser::Solve(string problem) {
    string solution;
   reverse(problem.begin(), problem.end());
   solution = problem;
   return solution;
}
