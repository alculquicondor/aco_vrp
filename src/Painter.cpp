#include "Painter.h"


const vector<vector<GLfloat>> Painter::colors = {
        {1, 0, 0},  // 0: red
        {0, 1, 0},  // 1: green
        {0, 0, 1},  // 2: blue
        {1, 1, 0},  // 3: yellow
        {0, 1, 1},  // 4: cyan
        {1, 0, 1},  // 5: magenta
        {.5, .5, 1},
        {1, .5, .5},
        {.5, 1, .5},
		{.5, .5, 0},
		{0, .5, .5},
		{.5, 0, .5},
		{1, 1, .5},
		{1, .5, 1},
		{.5, 1, 1},
		{0, .5, 1},
		{0, 1, .5},
		{.5, 0, 1},
		{.5, 1, 0},
		{1, 0, .5},
		{1, .5, 0}
};


void Painter::drawCity(const Location &loc) {
    glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2f(loc.x -  sqrt(loc.weight + 1), loc.y - sqrt(loc.weight + 1));
	glVertex2f(loc.x -  sqrt(loc.weight + 1), loc.y + sqrt(loc.weight + 1));
	glVertex2f(loc.x +  sqrt(loc.weight + 1), loc.y + sqrt(loc.weight + 1));
	glVertex2f(loc.x +  sqrt(loc.weight + 1), loc.y - sqrt(loc.weight + 1));
	glVertex2f(loc.x -  sqrt(loc.weight + 1), loc.y - sqrt(loc.weight + 1));
	glEnd();
}


void Painter::drawRoute(const Location &A, const Location &B, size_t col) {
	glColor3f(colors[col][0], colors[col][1], colors[col][2]);
	glBegin(GL_LINES);
	glVertex2f(A.x, A.y);
	glVertex2f(B.x, B.y);
	glEnd();
}
