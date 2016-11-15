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
    }
}


void Game::draw() {
    Painter p;
    for (auto &x : locations)
        p.drawCity(x);

    if (training) {
        auto sol = g->getBestSolution();
        size_t prev = 0;
        int col = 0, attended = 0;
        double distance = 0;
        for (size_t cur : sol) {
            p.drawRoute(locations[prev], locations[cur], col);
            if (cur == 0)
                ++col;
            else
                attended += locations[cur].weight;
            distance += locations[prev].distance(locations[cur]);
            prev = cur;
        }
        std::cout << std::setw(9) << iterations << ": " << std::setw(4) << attended << ' ' << std::fixed << std::setprecision(2)
                  << distance << std::endl;
    }
}


void Game::load_data(std::string filename) {
    std::ifstream input(filename);
    std::size_t n;
    input >> n;
    locations.resize(n);
    for (auto &x : locations) {
        input >> x.x >> x.y >> x.weight;
    }
}

void Game::set_training(bool ok) {
    if (not training and ok){
        g = new Graph(locations, 5, 20);
        iterations = 0;
        g->train(1000, 1, 100000, true);
    }
    training = ok;
}
