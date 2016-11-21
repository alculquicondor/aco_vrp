#ifndef ACOVRP_PAINTER_H
#define ACOVRP_PAINTER_H

#include <utility>
#include <vector>
#include <GL/gl.h>
#include <GL/glut.h>

#include "Location.h"


using std::vector;

class Painter {
private:
    static const vector<vector<GLfloat>> colors;

public:
    void drawCity(const Location &loc);
    void drawRoute(const Location &A, const Location &B, size_t col);
};

#endif //ACOVRP_PAINTER_H
