//
// AcornBusTwoRideEachTaste 2016.06.04
// Framebuffers for fluid simulation
//

#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>

class FluidFB {
private:
	GLuint fbPhysicalStepPre;
	GLuint fbPhysicalStepPost;
	GLuint fbPhysicalStepPostBack;
	GLuint fbNeighborPush;
	GLuint fbNeighborBlind;
	GLuint pos, vel, prop, etc, neighbor, dep;
	GLuint posback, velback;
	GLuint depPhysicalStepPre, depPhysicalStepPost, depPhysicalStepPostBack, depNeighborPush, depNeighborBlind;
	GLsizei particleSpaceW, particleSpaceH;
	GLsizei neighborSpaceW, neighborSpaceH;

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

	void generate();
	void init(
		unsigned int particleMax,
		float sep,
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
};