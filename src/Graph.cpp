#include "Graph.h"


Graph::Graph(const vector<Location> &location, int vehicles, int max_cap) :
        n(location.size()), vehicles(vehicles), max_cap(max_cap), location(location) {
    distance = new double *[n];
    distance[0] = new double[n * n];
    for (int i = 1; i < n; ++i)
        distance[i] = distance[i - 1] + n;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j)
            distance[i][j] = distance[j][i] = location[i].distance(location[j]);
        distance[i][i] = 0;
    }
}


Graph::~Graph() {
    delete[] distance[0];
    delete[] distance;
}


vector<int> Graph::buildSolution() {
    vector<int> solution(vehicles + n - 1);
    return solution;
}


double Graph::train(double t0, int ants, int max_repetitions) {
    pheromone = new double *[vehicles + n];

    std::fill(pheromone[0], pheromone[0] + n * n, t0);
    for (int r = 0; r < max_repetitions; ++r) {
        for (int a = 0; a < ants; ++a) {
            auto solution = buildSolution();
        }
    }
}