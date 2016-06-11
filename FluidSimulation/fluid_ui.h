//
// AcornBusTwoRideEachTaste 2016.06.10
// Fluid simulation UI
//

#pragma once

#include <GL/glew.h>

#include <GL/freeglut.h>
#include "texture.h"

class FluidUI {
private:
	static float viewAngleZ;
	static float viewAngleY;
	static int mouse_px, mouse_py;
	static bool pressed;
	Texture texCircle;

	GLuint shdRender;
	GLuint uniRDmatModelView;
	GLuint uniRDmatProjection;

	GLuint shdLinecube;
	GLuint uniLCmatModelView;
	GLuint uniLCmatProjection;
	GLuint vboLinecube;
	unsigned int vboLinecubeSize;

	float physicalSpaceX, physicalSpaceY, physicalSpaceZ;
	float viewDist;

public:
	static void mousefunction(int button, int state, int x, int y);
	static void motionfunction(int x, int y);
	void init(
		float physicalSpaceX, 
		float physicalSpaceY, 
		float physicalSpaceZ);
	void draw(
		GLuint vboParticleForEach,
		unsigned int particleMax,
		GLuint mapPosition,
		GLuint mapVelocity,
		GLuint mapETC);
};