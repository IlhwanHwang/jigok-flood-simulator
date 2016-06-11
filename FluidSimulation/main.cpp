//
// AcornBusTwoRideEachTaste 2016.06.03
// CSED451 Project
//

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "key.h"
#include "fluid.h"
#include "debug.h"

Fluid fluid;

void update(int cnt) {
	glutTimerFunc(16, update, cnt + 1);

	if (Key::keyCheckOn('a')) {
		fluid.update();
		errorecho("update");
	}

	Key::keyUpdate();

	fluid.draw();
}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1920, 1920);
	glutCreateWindow("AcornBusTwoRideEachTaste");
	glewInit();

	glEnable(GL_DEPTH);
	glDepthFunc(GL_LEQUAL);

	glutTimerFunc(16, update, 0);

	glutKeyboardFunc(Key::keyPressed);
	glutKeyboardUpFunc(Key::keyReleased);

	fluid.init();

	glutMainLoop();
}