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
#include "config.h"

Fluid fluid;

void update(int cnt) {
	glutTimerFunc(100, update, cnt + 1);

	//if (Key::keyCheckOn('a')) {
		fluid.update();
		errorecho("update");
	//}

	Key::keyUpdate();

	fluid.draw();
}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("AcornBusTwoRideEachTaste");
	glewInit();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glutTimerFunc(16, update, 0);

	glutKeyboardFunc(Key::keyPressed);
	glutKeyboardUpFunc(Key::keyReleased);

	fluid.init();

	glutMainLoop();
}