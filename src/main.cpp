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
    return 0;
}