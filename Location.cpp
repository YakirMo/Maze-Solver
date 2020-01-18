//
// Created by yakir on 1/18/20.
//

#include "Location.h"

using namespace std;

Location::Location(double x, double y) {
    this->location.first = x;
    this->location.second= y;
}
Location::~Location() {}

bool Location::equals(Location *loc) {
    return (this->location.first == loc->location.first) &&
            (this->location.second == loc->location.second);
}