#include "Painter.h"


const int Painter::CELL = 2;

const vector<vector<GLfloat>> Painter::colors = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
        {1, 1, 0},
        {0, 1, 1},
        {1, 0, 1}
};


void Painter::drawCity(int x, int y) {
	glBegin(GL_POLYGON);
	glVertex2f(x - CELL, y - CELL);
	glVertex2f(x - CELL, y + CELL);
	glVertex2f(x + CELL, y + CELL);
	glVertex2f(x + CELL, y - CELL);
	glVertex2f(x - CELL, y - CELL);
	glEnd();
}


void Painter::drawRoute(pair<int, int > A , pair<int, int> B, int col ) {
	glColor3f(colors[col][0], colors[col][1], colors[col][2]);
	glBegin(GL_LINES);
	glVertex2f(A.first, A.second);
	glVertex2f(B.first, B.second);
	glEnd();
}
