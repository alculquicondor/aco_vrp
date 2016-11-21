#include "Game.h"


Game::Game() : training(false), g(nullptr) {
}


Game::~Game() {
    if (g != nullptr)
        delete g;
}


void Game::tick() {
    draw();
    if (training) {
        g->train(1000, 1);
        ++iterations;
        if (iterations == 100) {
            set_training(false);
        }
    }
}


void Game::draw() {
    Painter p;
    for (auto &x : locations)
        p.drawCity(x);

    if (g == nullptr)
        return;
    auto sol = g->getBestSolution();
    size_t prev = 0;
    int col = 0, attended = 0;
    double distance = 0;
    for (auto cur : sol) {
        p.drawRoute(locations[prev], locations[cur.first], cur.second);
        if (cur.first != 0)
            attended += locations[cur.first].weight;
        distance += locations[prev].distance(locations[cur.first]);
        prev = cur.first;
    }
    if (training)
        std::cout << col << ' ' << std::setw(9) << iterations << ": " << std::setw(4) << attended << ' '
                  << std::fixed << std::setprecision(2) << distance << std::endl;
}


void Game::load_data(std::string filename) {
    std::ifstream input(filename);
    std::size_t n;

    input >> n;  // number of locations
    locations.resize(n);
    for (auto &x : locations)
        input >> x.x >> x.y >> x.weight;

    input >> n;  // number of vehicles
    vehicles.resize(n);
    for (auto &x: vehicles)
        input >> x;
}

void Game::set_training(bool ok) {
    if (not training and ok){
        std::size_t total_weight = 0;
        for (auto x : locations)
            total_weight += x.weight;
        g = new Graph(locations, vehicles);
        iterations = 0;
        g->train(1000, 1, sqrt(total_weight), true);
    }
    training = ok;
}
