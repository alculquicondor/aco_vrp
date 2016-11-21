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
public:
    using Solution = std::vector<std::pair<size_t, size_t>>;

private:
    static const double alpha, beta, rho;

    size_t n, m;
    vector<Location> location;
    vector<std::size_t> vehicles;
    double **distance, **pheromone, **tmp_pheromone;
    double bestFitness;
    Solution bestSolution;

    std::mt19937 gen;

    double probability(size_t i, size_t j, bool vehicle = false);

    double getFitness(const Solution &solution);

    void updatePheromone(double **pher, const Solution &solution, double add);

    void evaporate();

public:
    Graph(const vector<Location> &location, const vector<size_t> &vehicles);
    ~Graph();

    void train(int ants, int max_repetitions, double t0=0, bool reset=false);
    Solution buildSolution();

    Solution getBestSolution() const {
        return bestSolution;
    }

    void showPheromones();
};


#endif //ACOVRP_GRAPH_H
