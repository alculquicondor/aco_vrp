#include <iostream>
#include <vector>

#include "Graph.h"

using namespace std;


int main() {
    vector<Location> loc = {
            {0, 0, 0},
            {5, 0, 10},
            {5, 5, 5},
            {-5, -5, 5},
            {-5, 0, 5},
            {-5, 5, 5}
    };

    Graph g(loc, 2, 20);

    g.train(5, 50, 100, true);
    auto sol = g.buildSolution();

    g.showPheromones();
    cout << 0;
    for (size_t x : sol)
        cout << ' ' << x;
    cout << endl;

    return 0;
}