//
// AcornBusTwoRideEachTaste 2016.06.04
// Fluid simulation (core)
//

#pragma once

#include "fluid_framebuffer.h"
#include "fluid_ui.h"
#include "texture.h"

class Fluid {
private:
	FluidFB fb;
	FluidUI ui;

	const unsigned int particleSpaceW;
	const unsigned int particleSpaceH;
	const unsigned int particleMax;

	const float h;

	const float physicalSpaceX;
	const float physicalSpaceY;
	const float physicalSpaceZ;

	const float neighborCellSizeX;
	const float neighborCellSizeY;
	const float neighborCellSizeZ;

	const unsigned int neighborCellNumX;
	const unsigned int neighborCellNumY;
	const unsigned int neighborCellNumZ;
	const unsigned int neighborCellLength;

	const unsigned int neighborSpaceW;
	const unsigned int neighborSpaceH;

	GLuint vboParticleForEach;
	GLuint vboNeighborForEach;

	void uniformNeighborGrid(GLuint program);
	void uniformMap(GLuint program);
	void uniformPhysical(GLuint program);

	GLuint shdNeighborPush;
	GLuint uniNPstagef;

	GLuint shdNeighborBlind;
	GLuint uniNBstageNormf;

	GLuint shdPhysicalStepPre;

	GLuint shdPhysicalStepPost;
	GLuint uniPTphysicalDeltaTime;

public:
	Fluid();
	void init();
	void draw();
	void update();
}; 