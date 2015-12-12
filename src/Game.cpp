#include "Game.h"


Game::Game() : training(false), g(nullptr) {
}


Game::~Game() {
    if (g != nullptr)
        delete g;
}


bool Game::is_training() {
    return training;
}


void Game::tick() {
    draw();
    if (training) {
        g->train(1000, 1);
    }
}


void Game::draw() {
    Painter p;
    for (int i = 0; i < V.size(); ++i)
        p.drawCity(V[i].first, V[i].second);

    if (training) {
        vector<size_t> sol = g->buildSolution(true);
        size_t prev = 0;
        int col = 0;
        for (size_t cur : sol) {
            p.drawRoute(V[prev], V[cur], col);
            if (cur == 0)
                ++col;
            prev = cur;
        }
    }
}


void Game::add(int x, int y) {
    V.push_back({x , y});
}


void Game::set_training(bool ok) {
    if (not training and ok){
        vector<Location> IG;
        for (auto a : V)
            IG.push_back({a.first, a.second, 1});
        g = new Graph(IG, 4, 8);
        g->train(1000, 1, 100000, true);
    }
    training = ok;
}
