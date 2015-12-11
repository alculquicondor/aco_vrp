#ifndef ACOVRP_PAINTER_H
#define ACOVRP_PAINTER_H

#include <utility>
#include <vector>
#include <GL/gl.h>
#include <GL/glut.h>

using std::vector;
using std::pair;

class Painter {
private:
    static const vector<vector<GLfloat>> colors;
    static const int CELL;

public:
    void drawCity(int x, int y);
    void drawRoute(pair<int, int> A, pair<int, int> B, int col);
};

#endif //ACOVRP_PAINTER_H
