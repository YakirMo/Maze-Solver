//
// Created by yakir on 1/18/20.
//

#ifndef EX4_SEARCH_H
#define EX4_SEARCH_H

#include "Isearchable.h"
#include "Isearcher.h"
#include "queue"
#include "stack"
#include "Compare.h"
#include "iostream"

using namespace std;

template<class S>
class Search : public Isearcher<S> {
private:
    priority_queue<State<Location *> *, vector<State<Location *> *>, Compare> priorQ;
    int checkedNodes = 0;
protected:
    virtual string search(Isearchable<S>* problem) = 0;

    void addToQ(State<Location *> *state) {
        this->priorQ.push(state);
    }

    State<Location *> *popQ() {
        this->checkedNodes += 1;
        State<Location *> *state = priorQ.top();
        this->priorQ.pop();
        return state;
    }

    void updateQ(State<Location *> *state) {
        int i;
        State<Location *> *curr1stElement;
        vector<State<Location *> *> removed;
        while (!this->priorQ.empty()) {
            curr1stElement = this->priorQ.top();
            if (curr1stElement->equal(*state)) {
                this->priorQ.pop();
                break;
            } else {
                removed.emplace_back(curr1stElement);
                this->priorQ.pop();
            }
        }
        for (i = 0; i < removed.size(); i++) {
            this->priorQ.emplace(removed[i]);
        }
    }

    bool inQ(State<Location *> *state) {
        int i;
        bool inQ = false;
        vector<State<Location *> *> removed;
        State<Location *> *curr1stElement;
        while (!this->priorQ.empty()) {
            curr1stElement = this->priorQ.top();
            if (curr1stElement->equal(*state)) {
                inQ = true;
                break;
            } else {
                removed.emplace_back(curr1stElement);
                this->priorQ.pop();
            }
        }
        for (i = 0; i < removed.size(); i++) {
            this->priorQ.emplace(removed[i]);
        }
        return inQ;
    }

    string getBackTrack(Isearchable<Location *> *problem) {
        double x, y;
        string backTrack;
        stack<string> paths;
        State<Location *> *successor = problem->getGoal();
        while (successor != problem->getInitState()) {
            paths.emplace(problem->direction(successor));
            successor = successor->getLastState();
        }
        //backTrack = to_string(getCheckedNodes()) + "\n";
        while(!paths.empty()) {
            backTrack.append(paths.top());
            paths.pop();
            if(paths.size() > 0) {
                backTrack.append(", ");
            }
        }
        cout<< backTrack << endl;
        cout<< "Number of vertexes visited:"  + getCheckedNodes() <<endl;
        return backTrack;
    }

public:

    void raiseCheckedNodes() {
        this->checkedNodes += 1;
    }

    int QSize() {
        return this->priorQ.size();
    }

    int getCheckedNodes() {
        return this->checkedNodes;
    }

    priority_queue<State<Location *> *, vector<State<Location *> *>, Compare> getQ() {
        return this->priorQ;
    }
};


#endif //EX4_SEARCH_H
