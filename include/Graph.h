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

    size_t n, m;
    vector<Location> location;
    vector<std::size_t> vehicles;
    double **distance, **pheromone, **tmp_pheromone;
    double bestFitness;
    vector<size_t> bestSolution;

    std::mt19937 gen;

    double probability(size_t i, size_t j, bool vehicle = false);

    double getFitness(vector<size_t> solution);

    void updatePheromone(double **pher, vector<size_t> solution, double add);

    void evaporate();

public:
    Graph(const vector<Location> &location, const vector<size_t> &vehicles);
    ~Graph();

    void train(int ants, int max_repetitions, double t0=0, bool reset=false);
    vector<size_t> buildSolution();

    vector<size_t> getBestSolution() const {
        return bestSolution;
    }

    void showPheromones();
};


#endif //ACOVRP_GRAPH_H
