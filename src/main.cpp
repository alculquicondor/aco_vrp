#include "Game.h"

using namespace std;


Game game;


void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	game.tick();
	glutSwapBuffers();
}


void process_Normal_Keys(unsigned char key, int x, int y) {
	switch (key) {
		case 'c':
			game.set_training(false) ;
			break;
		case 's':
			game.set_training(true) ;
			break;
        default: break;
	}
    glutPostRedisplay();
}


void timer(int=0) {
   display();
   glutTimerFunc(1, timer, 0);
}


int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 120);
	glutCreateWindow("Ant Colony Optimization");
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -1.0, 1.0);
	glutDisplayFunc(display);
    glutKeyboardFunc(process_Normal_Keys);
	timer();

	if (argc < 2) {
		std::cerr << "input file missing" << std::endl;
	}
	game.load_data(argv[1]);

	glutMainLoop();
}
