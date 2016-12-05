#include "Graph.h"
#include <cassert>


const double Graph::alpha = .5;
const double Graph::beta = 3;
const double Graph::rho = .1;


double Graph::probability(size_t i, size_t j, bool vehicle) {
    double prob = pow(pheromone[vehicle ? i : vehicles.size() + i][j], alpha) *
            pow(1. / log(distance[vehicle ? 0 : i][j]), beta);

    assert(prob < 1e300);
    return prob;
}


double Graph::getFitness(double total_weight, double total_distance) {
    return sqrt(total_weight) * (1 + 1 / total_distance);
}


double Graph::getFitness(const Solution &solution) {
    double total_dist = 0;
    size_t curr_loc = 0, weight = 0;
    for (auto loc : solution) {
        total_dist += distance[loc.first][curr_loc];
        curr_loc = loc.first;
        if (loc.first != 0)
            weight += location[loc.first].weight;
    }
    return getFitness(weight, total_dist);
}


void Graph::updatePheromone(double **pher, const Solution &solution, double add) {
    size_t curr_loc = 0;
    size_t vehicle = 0;
    for (auto loc : solution) {
        if (curr_loc == 0) {
            pher[vehicle][loc.first] += add;
            ++vehicle;
        } else {
            pher[vehicles.size() + curr_loc][loc.first] += add;
        }
        curr_loc = loc.first;
    }
}


void Graph::evaporate() {
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            pheromone[i][j] *= 1 - rho;
}


Graph::Graph(const vector<Location> &location, const vector<size_t> &vehicles, double maxDist) :
        n(location.size()), vehicles(vehicles), location(location), m(n + vehicles.size()),
        maxDist(maxDist), gen(std::random_device()()), bestFitness(0) {
    distance = new double*[n];
    distance[0] = new double[n * n];
    for (int i = 1; i < n; ++i)
        distance[i] = distance[i - 1] + n;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j)
            distance[i][j] = distance[j][i] = location[i].distance(location[j]);
        distance[i][i] = 50;  // to allow to return to base
    }

    pheromone = new double*[m];
    tmp_pheromone = new double*[m];
    pheromone[0] = new double[m * n];
    tmp_pheromone[0] = new double[m * n];
    for (int i = 1; i < m; ++i) {
        pheromone[i] = pheromone[i - 1] + n;
        tmp_pheromone[i] = tmp_pheromone[i - 1] + n;
    }
}


Graph::~Graph() {
    delete[] distance[0];
    delete[] distance;

    delete[] pheromone[0];
    delete[] pheromone;

    delete[] tmp_pheromone[0];
    delete[] tmp_pheromone;
}


void Graph::train(int ants, int max_repetitions, double t0, bool reset) {
    if (reset)
        std::fill(pheromone[0], pheromone[0] + m * n, t0);

    for (int r = 0; r < max_repetitions; ++r) {
        double total_pheromone = 0;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < m; ++j)
                total_pheromone += pheromone[i][j];
        evaporate();
        std::copy(pheromone[0], pheromone[0] + m * n, tmp_pheromone[0]);
        for (int a = 0; a < ants; ++a) {
            auto solution = buildSolution();
            double fitness = getFitness(solution);
            updatePheromone(tmp_pheromone, solution, fitness / ants);
            if (fitness > bestFitness) {
                bestSolution = solution;
                bestFitness = fitness;
            }
        }
        std::copy(tmp_pheromone[0], tmp_pheromone[0] + m * n, pheromone[0]);
    }
}


typename Graph::Solution Graph::buildSolution() {
    Solution solution;
    vector<bool> seen(n);
    size_t curr_loc = 0, prev_loc = 0, clients = 0, vehicle = 0, cap = vehicles[0];
    double vehicle_dist = 0;
    while (clients < n - 1 and vehicle < vehicles.size()) {
        seen[curr_loc] = true;
        vector<size_t> options;
        vector<double> distribution;
        if (vehicle_dist < maxDist) {
            for (size_t j = 1; j < n; ++j)
                if (not seen[j] and location[j].weight <= cap) {
                    options.push_back(j);
                    distribution.push_back(probability(curr_loc == 0 ? vehicle : curr_loc, j, curr_loc == 0));
                }
        }
        options.push_back(0);
        distribution.push_back(probability(curr_loc == 0 ? vehicle : curr_loc, 0, curr_loc == 0));

        for (size_t k = 1; k < distribution.size(); ++k)
            distribution[k] += distribution[k - 1];

        prev_loc = curr_loc;
        curr_loc = options[std::upper_bound(distribution.begin(), distribution.end(),
                                            std::uniform_real_distribution<>(0., distribution.back())(gen))
                           - distribution.begin()];
        assert(curr_loc < location.size());
        solution.push_back({curr_loc, vehicle});
        cap -= location[curr_loc].weight;
        if (curr_loc != prev_loc)
            vehicle_dist += location[prev_loc].distance(location[curr_loc]);
        if (curr_loc == 0) {
            if (prev_loc == 0) {
                if (++vehicle < vehicles.size()) {
                    cap = vehicles[vehicle];
                    vehicle_dist = 0;
                }
            } else {
                cap = vehicles[vehicle];
            }
        } else {
            ++clients;
        }
    }
    if (solution.back().first != 0)
        solution.push_back({0, vehicle});
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
