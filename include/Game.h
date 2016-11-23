#ifndef ACOVRP_GAME_H
#define ACOVRP_GAME_H

#include <fstream>
#include <iomanip>

#include "Graph.h"
#include "Painter.h"


using std::pair;

extern const int width, height;

extern const size_t ants;

class Game
{
private:
    Graph *g;
    bool training;
    vector<Location> locations;
    vector<std::size_t> vehicles;
    std::size_t iterations;

public:
    Game();
    ~Game();

    void draw();
    void load_data(std::string filename);
    void set_training(bool ok );
    void tick();
};

#endif //ACOVRP_GAME_H
