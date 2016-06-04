//
// AcornBusTwoRideEachTaste 2016.06.03
// CSED451 Project
//

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "key.h"

void update(int cnt) {
	glutTimerFunc(16, update, cnt + 1);
}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(512, 512);
	glutCreateWindow("AcornBusTwoRideEachTaste");
	glewInit();

	glutTimerFunc(16, update, 0);

	glutKeyboardFunc(Key::keyPressed);
	glutKeyboardUpFunc(Key::keyReleased);

	glutMainLoop();
}