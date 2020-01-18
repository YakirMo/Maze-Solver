//
// Created by yakir on 1/18/20.
//

#ifndef EX4_LOCATION_H
#define EX4_LOCATION_H

#include "utility"


using namespace std;

class Location {
public:
    pair<double, double> location;

    Location(double x, double y);
    ~Location();
    bool equals(Location *loc);
};


#endif //EX4_LOCATION_H
