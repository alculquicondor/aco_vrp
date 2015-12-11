#include "Game.h"

using namespace std;


Game game;


void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	game.tick();
	glutSwapBuffers();
}


void mouse(int button, int state, int x, int y) {
	if (state == GLUT_UP) {
		switch (button) {
			case GLUT_LEFT_BUTTON:
				if (!game.is_training())
				   game.add(x, y);
				break;
            default: break;
		}
		glutPostRedisplay();
	}
}


void process_Normal_Keys(unsigned char key, int x, int y) {
	switch (key) {
		case 'n': 
		        game = Game();	
			break;
		case 'c': 
			game.set_training( false ) ;
			break;
		case 's': 
			game.set_training( true ) ;
			break;
        default: break;
	}
    glutPostRedisplay();
}


void timer(int=0) {
   display();
   glutTimerFunc(60, timer, 0);
}


int main(int argc, char **argv) {
    const int width = 800, height = 500;
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
	glutMouseFunc(mouse);
    glutKeyboardFunc(process_Normal_Keys);
	timer();
	glutMainLoop();
}
