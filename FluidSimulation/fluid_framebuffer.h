//
// AcornBusTwoRideEachTaste 2016.06.04
// Framebuffers for fluid simulation
//

#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>

#include "model.h"
#include "mat.h"

class FluidFB {
private:
	GLuint fbPhysicalStepPre;
	GLuint fbPhysicalStepPost;
	GLuint fbPhysicalStepPostBack;
	GLuint fbNeighborPush;
	GLuint fbNeighborBlind;
	GLuint pos, vel, prop, etc, norm, neighbor, dep;
	GLuint posback, velback;
	GLuint fbEnvironment;
	GLuint env;
	GLuint depPhysicalStepPre, depPhysicalStepPost, depPhysicalStepPostBack, depNeighborPush, depNeighborBlind;
	GLsizei particleSpaceW, particleSpaceH;
	GLsizei neighborSpaceW, neighborSpaceH;

	unsigned int envResolutionX;
	unsigned int envResolutionY;
	unsigned int envResolutionZ;

	unsigned int particleActive;
	unsigned int particleMax;

	GLuint shdSprite;
	GLuint uniSPmatModelView;
	GLuint uniSPmatProjection;
	GLuint uniSPwidth;
	GLuint uniSPheight;
	GLuint uniSPbias;
	GLuint uniSPscale;
	GLuint vboZeropoint;

	void drawBuffer(GLuint buffer, float x, float y, float scale, float bias);

public:
	FluidFB() {}
	FluidFB(GLsizei psw, GLsizei psh, GLsizei nsw, GLsizei nsh)
		: particleSpaceW(psw), particleSpaceH(psh), neighborSpaceW(nsw), neighborSpaceH(nsh) {
		std::cout << "FrameBuffer particleSpaceW: " << particleSpaceW << std::endl;
		std::cout << "FrameBuffer particleSpaceH: " << particleSpaceH << std::endl;
		std::cout << "FrameBuffer neighborSpaceW: " << neighborSpaceW << std::endl;
		std::cout << "FrameBuffer neighborSpaceH: " << neighborSpaceH << std::endl;
	}

	void generate(
		unsigned int envResolutionX,
		unsigned int envResolutionY,
		unsigned int envResolutionZ);
	void init(unsigned int particleMax);
	void initPos(
		unsigned int particleMax,
		float h,
		float physicalSpaceX,
		float physicalSpaceY,
		float physicalSpaceZ);
	void initEnv(
		Model& model,
		mat4& matEnvModelview,
		float physicalSpaceX,
		float physicalSpaceY,
		float physicalSpaceZ);

	void debugdraw();
	void swap();
	void bind();

	void outputPhysicalStepPre() { glViewport(0, 0, particleSpaceW, particleSpaceH); glBindFramebuffer(GL_FRAMEBUFFER, fbPhysicalStepPre); }
	void outputPhysicalStepPost() { glViewport(0, 0, particleSpaceW, particleSpaceH); glBindFramebuffer(GL_FRAMEBUFFER, fbPhysicalStepPostBack); }
	void outputNeighborPush() { glViewport(0, 0, neighborSpaceW, neighborSpaceH); glBindFramebuffer(GL_FRAMEBUFFER, fbNeighborPush); }
	void outputNeighborBlind() { glViewport(0, 0, particleSpaceW, particleSpaceH); glBindFramebuffer(GL_FRAMEBUFFER, fbNeighborBlind); }
	void outputScreen() { glViewport(0, 0, particleSpaceW, particleSpaceH); glBindFramebuffer(GL_FRAMEBUFFER, 0); }

	GLuint mapPosition() { return pos; }
	GLuint mapVelocity() { return vel; }
	GLuint mapProperty() { return prop; }
	GLuint mapETC() { return etc; }
	GLuint mapNeighbor() { return neighbor; }
	GLuint mapWallField() { return env; }
	GLuint mapNorm() { return norm; }
};