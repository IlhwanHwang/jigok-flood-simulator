//
// AcornBusTwoRideEachTaste 2016.06.04
// Framebuffers for fluid simulation
//

#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>

class FBfluid {
private:
	GLuint fbPhysicalStepPre;
	GLuint fbPhysicalStepPost;
	GLuint fbNeighborPush;
	GLuint fbNeighborBlind;
	GLuint pos, vel, prop, etc, neighbor, dep;
	GLuint depPhysicalStepPre, depPhysicalStepPost, depNeighborPush, depNeighborBlind;
	GLsizei particleSpaceW, particleSpaceH;
	GLsizei neighborSpaceW, neighborSpaceH;

public:
	FBfluid(GLsizei psw, GLsizei psh, GLsizei nsw, GLsizei nsh)
		: particleSpaceW(psw), particleSpaceH(psh), neighborSpaceW(nsw), neighborSpaceH(nsh) {}

	void generate();
	void outputPhysicalStepPre() { glBindFramebuffer(GL_FRAMEBUFFER, fbPhysicalStepPre); }
	void outputPhysicalStepPost() { glBindFramebuffer(GL_FRAMEBUFFER, fbPhysicalStepPost); }
	void outputNeighborPush() { glBindFramebuffer(GL_FRAMEBUFFER, fbNeighborPush); }
	void outputNeighborBlind() { glBindFramebuffer(GL_FRAMEBUFFER, fbNeighborBlind); }
	void outputScreen() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
	void inputPhysicalStepPre() {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, pos);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, neighbor);
	}
	void inputPhysicalStepPost() {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, pos);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, vel);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, prop);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, neighbor);
	}
	void inputNeighborPush() {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, pos);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, etc);
	}
	void inputNeighborBlind() {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, neighbor);
	}
	void inputVTF() {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, pos);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, prop);
	}
};