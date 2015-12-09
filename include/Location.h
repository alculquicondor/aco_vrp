#ifndef ACOVRP_POINT_H
#define ACOVRP_POINT_H

#include <cmath>


struct Location {
    int x, y, weight;

    double distance(const Location &o) const {
        return hypot(x - o.x, y - o.y);
    }
};

#endif //ACOVRP_POINT_H
