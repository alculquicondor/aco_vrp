#include "Painter.h"


const vector<vector<GLfloat>> Painter::colors = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
        {1, 1, 0},
        {0, 1, 1},
        {1, 0, 1}
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


void Painter::drawRoute(const Location &A, const Location &B, int col) {
	glColor3f(colors[col][0], colors[col][1], colors[col][2]);
	glBegin(GL_LINES);
	glVertex2f(A.x, A.y);
	glVertex2f(B.x, B.y);
	glEnd();
}
