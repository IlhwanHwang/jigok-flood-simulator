//
// AcornBusTwoRideEachTaste 2016.06.04
// Framebuffers for fluid simulation
//

#include "fluid_framebuffer.h"
#include "debug.h"

void FBfluid::generate() {
	glGenFramebuffers(1, &fbPhysicalStepPre);
	glGenFramebuffers(1, &fbPhysicalStepPost);
	glGenFramebuffers(1, &fbNeighborPush);
	glGenFramebuffers(1, &fbNeighborBlind);

	glGenTextures(1, &pos);
	glBindTexture(GL_TEXTURE_2D, pos);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, particleSpaceW, particleSpaceH, 0, GL_RGB, GL_FLOAT, NULL);

	glGenTextures(1, &vel);
	glBindTexture(GL_TEXTURE_2D, vel);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, particleSpaceW, particleSpaceH, 0, GL_RGB, GL_FLOAT, NULL);

	glGenTextures(1, &prop);
	glBindTexture(GL_TEXTURE_2D, prop);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RG32F, particleSpaceW, particleSpaceH, 0, GL_RG, GL_FLOAT, NULL);

	glGenTextures(1, &etc);
	glBindTexture(GL_TEXTURE_2D, etc);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, particleSpaceW, particleSpaceH, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glGenTextures(1, &neighbor);
	glBindTexture(GL_TEXTURE_2D, neighbor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RG32F, neighborSpaceW, neighborSpaceH, 0, GL_RG, GL_FLOAT, NULL);

	glGenTextures(1, &depPhysicalStepPre);
	glBindTexture(GL_TEXTURE_2D, depPhysicalStepPre);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, particleSpaceW, particleSpaceH, 0,
		GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);

	glGenTextures(1, &depPhysicalStepPost);
	glBindTexture(GL_TEXTURE_2D, depPhysicalStepPost);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, particleSpaceW, particleSpaceH, 0,
		GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);

	glGenTextures(1, &depNeighborPush);
	glBindTexture(GL_TEXTURE_2D, depNeighborPush);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, neighborSpaceW, neighborSpaceH, 0,
		GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);

	glGenTextures(1, &depNeighborBlind);
	glBindTexture(GL_TEXTURE_2D, depNeighborBlind);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, neighborSpaceW, neighborSpaceH, 0,
		GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);

	glBindFramebuffer(GL_FRAMEBUFFER, fbPhysicalStepPre);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, prop, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depPhysicalStepPre, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, fbPhysicalStepPost);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pos, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, vel, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depPhysicalStepPost, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, fbNeighborPush);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, neighbor, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depNeighborPush, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, fbNeighborBlind);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, etc, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depNeighborBlind, 0);

	fberrorecho();
}