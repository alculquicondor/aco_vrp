#ifndef ACOVRP_GRAPH_H
#define ACOVRP_GRAPH_H

#include <vector>
#include <algorithm>

#include "Location.h"

using std::vector;


class Graph {
private:
    int n, vehicles, max_cap;
    vector<Location> location;
    double **distance, **pheromone;
    vector<int> buildSolution();

public:
    Graph(const vector<Location> &location, int vehicles, int max_cap);
    ~Graph();

    double train(double t0, int ants, int max_repetitions);
};


#endif //ACOVRP_GRAPH_H
