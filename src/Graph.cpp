#include "Graph.h"
#include <cassert>


const double Graph::alpha = 1;
const double Graph::beta = 1.4;
const double Graph::rho = .1;


double Graph::probability(size_t i, size_t j, bool vehicle) {
    double prob = pow(pheromone[vehicle ? i : vehicles + i][j], alpha) *
           pow(1. / distance[vehicle ? 0 : i][j], beta);
    assert(prob < 1e300);
    return prob;
}

double Graph::getFitness(vector<size_t> solution) {
    double total_dist = 0;
    size_t curr_loc = 0, clients = 0;
    for (size_t loc : solution) {
        total_dist += distance[loc][curr_loc];
        curr_loc = loc;
        clients += loc != 0;
    }
    return sqrt(clients) * (1 + 1 / log(total_dist));
}


void Graph::updatePheromone(double **pher, vector<size_t> solution, double add) {
    size_t curr_loc = 0;
    size_t vehicle = 0;
    for (size_t loc : solution) {
        if (curr_loc == 0) {
            pher[vehicle][loc] += add;
            ++vehicle;
        } else {
            pher[vehicles + curr_loc][loc] += add;
        }
        curr_loc = loc;
    }
}


void Graph::evaporate() {
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            pheromone[i][j] *= 1 - rho;
}


Graph::Graph(const vector<Location> &location, size_t vehicles, size_t max_cap) :
        n(location.size()), vehicles(vehicles), max_cap(max_cap), location(location), m(n + vehicles),
        gen(std::random_device()()), bestFitness(0) {
    distance = new double*[n];
    distance[0] = new double[n * n];
    for (int i = 1; i < n; ++i)
        distance[i] = distance[i - 1] + n;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j)
            distance[i][j] = distance[j][i] = location[i].distance(location[j]);
        distance[i][i] = 1e300;
    }

    pheromone = new double*[m];
    pheromone[0] = new double[m * n];
    for (int i = 1; i < m; ++i)
        pheromone[i] = pheromone[i - 1] + n;
}


Graph::~Graph() {
    delete[] distance[0];
    delete[] distance;

    delete[] pheromone[0];
    delete[] pheromone;
}


void Graph::train(int ants, int max_repetitions, double t0, bool reset) {
    if (reset)
        std::fill(pheromone[0], pheromone[0] + m * n, t0);

    double **tmp = new double*[m];
    tmp[0] = new double[m * n];
    for (int i = 1; i < m; ++i)
        tmp[i] = tmp[i - 1] + n;

    for (int r = 0; r < max_repetitions; ++r) {
        evaporate();
        std::copy(pheromone[0], pheromone[0] + m * n, tmp[0]);
        for (int a = 0; a < ants; ++a) {
            auto solution = buildSolution();
            double fitness = getFitness(solution);
            updatePheromone(tmp, solution, fitness);
            if (fitness > bestFitness) {
                bestSolution = solution;
                bestFitness = fitness;
            }
        }
        std::copy(tmp[0], tmp[0] + m * n, pheromone[0]);
    }

    delete[] tmp[0];
    delete[] tmp;
}


vector<size_t> Graph::buildSolution() {
    vector<size_t> solution;
    vector<bool> seen(n);
    size_t curr_loc = 0, clients = 0, vehicle = 0, cap = max_cap;
    for (int i = 0; clients < n - 1 and vehicle < vehicles; ++i) {
        seen[curr_loc] = true;
        vector<size_t> options;
        vector<double> distribution{0};
        if (curr_loc == 0) {
            for (size_t j = 1; j < n; ++j)
                if (not seen[j] and location[j].weight <= cap) {
                    options.push_back(j);
                    distribution.push_back(distribution.back() + probability(vehicle, j, true));
                }
        } else {
            bool has_exit = false;
            for (size_t j = 1; j < n; ++j)
                if (not seen[j] and location[j].weight <= cap) {
                    options.push_back(j);
                    distribution.push_back(distribution.back() + probability(curr_loc, j));
                    has_exit = true;
                }
            if (not has_exit) {  // return to base
                options.push_back(0);
                distribution.push_back(distribution.back() + probability(curr_loc, 0));
            }
        }
        curr_loc = options[std::upper_bound(distribution.begin(), distribution.end(),
                                            std::uniform_real_distribution<>(0., distribution.back())(gen))
                           - distribution.begin() - 1];
        assert(curr_loc < location.size());
        solution.push_back(curr_loc);
        cap -= location[curr_loc].weight;
        if (curr_loc == 0) {
            ++vehicle;
            cap = max_cap;
        } else {
            ++clients;
        }
    }
    if (solution.back() != 0)
        solution.push_back(0);
    return solution;
}

void Graph::showPheromones() {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j)
            std::cout << pheromone[i][j] << ' ';
        std::cout << std::endl;
    }
    std::cout << "---------" << std::endl;
}
