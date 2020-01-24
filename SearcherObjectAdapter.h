//
// Created by yakir on 1/19/20.
//

#ifndef EX4_SEARCHEROBJECTADAPTER_H
#define EX4_SEARCHEROBJECTADAPTER_H

#include "Solver.h"
#include "Isearchable.h"
#include "Isearcher.h"
#include "string"
#include "Location.h"
#include "Search.h"

template <class S>
class SearcherObjectAdapter : public Solver<Isearchable<S>*, string> {
public:
    Isearcher<S> *searcher;
    explicit SearcherObjectAdapter(Isearcher<S> *search) {
        searcher = search;
    }
    string Solve(Isearchable<S> *prob) {
        auto* solver =  searcher;
        return solver->search(prob);
    }
};

#endif //EX4_SEARCHEROBJECTADAPTER_H
