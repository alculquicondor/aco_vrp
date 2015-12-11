#ifndef ACOVRP_GAME_H
#define ACOVRP_GAME_H

#include <utility>

#include "Graph.h"
#include "Painter.h"


using std::pair;


class Game
{
private:
    Graph *g;
    bool training;
    vector<pair<int, int>>  V ;

public:
    Game();
    ~Game();

    void draw();
    void add(int x, int y);
    void set_training(bool ok );
    bool is_training();
    void tick();
};

#endif //ACOVRP_GAME_H
