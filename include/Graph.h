#ifndef ACOVRP_GRAPH_H
#define ACOVRP_GRAPH_H

#include <algorithm>
#include <cmath>
#include <random>
#include <vector>
#include <iostream>

#include "Location.h"

using std::vector;


class Graph {
private:
    static const double alpha, beta, rho;

    size_t n, vehicles, max_cap, m;
    vector<Location> location;
    double **distance, **pheromone;
    std::mt19937 gen;

    double probability(size_t i, size_t j, bool vehicle = false);
    void updatePheromone(double **pher, vector<size_t> solution);
    void evaporate();

public:
    Graph(const vector<Location> &location, size_t vehicles, size_t max_cap);
    ~Graph();

    void train(int ants, int max_repetitions, double t0, bool reset=true);
    vector<size_t> buildSolution(bool best=false);

    void showPheromones();
};


#endif //ACOVRP_GRAPH_H
