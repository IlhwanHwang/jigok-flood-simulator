//
// AcornBusTwoRideEachTaste 2016.06.04
// Framebuffers for fluid simulation
//

#include "fluid_framebuffer.h"
#include "debug.h"
#include "shader.h"

#include <vector>
#include <iostream>

#include "mat.h"

void FluidFB::generate() {
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

	glGenTextures(1, &posback);
	glBindTexture(GL_TEXTURE_2D, posback);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, particleSpaceW, particleSpaceH, 0, GL_RGB, GL_FLOAT, NULL);

	glGenTextures(1, &velback);
	glBindTexture(GL_TEXTURE_2D, velback);
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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, particleSpaceW, particleSpaceH, 0, GL_RG, GL_UNSIGNED_BYTE, NULL);

	glGenTextures(1, &neighbor);
	glBindTexture(GL_TEXTURE_2D, neighbor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, neighborSpaceW, neighborSpaceH, 0, GL_RGB, GL_FLOAT, NULL);

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

	glGenTextures(1, &depPhysicalStepPostBack);
	glBindTexture(GL_TEXTURE_2D, depPhysicalStepPostBack);
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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, particleSpaceW, particleSpaceH, 0,
		GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);

	glGenFramebuffers(1, &fbPhysicalStepPre);
	glBindFramebuffer(GL_FRAMEBUFFER, fbPhysicalStepPre);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, prop, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depPhysicalStepPre, 0);
	fberrorecho();
	
	glGenFramebuffers(1, &fbPhysicalStepPost);
	glBindFramebuffer(GL_FRAMEBUFFER, fbPhysicalStepPost);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pos, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, vel, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depPhysicalStepPost, 0);
	GLenum buf[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(2, buf);
	fberrorecho();
	
	glGenFramebuffers(1, &fbPhysicalStepPostBack);
	glBindFramebuffer(GL_FRAMEBUFFER, fbPhysicalStepPostBack);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, posback, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, velback, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depPhysicalStepPostBack, 0);
	GLenum buf2[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(2, buf2);
	fberrorecho();

	glGenFramebuffers(1, &fbNeighborPush);
	glBindFramebuffer(GL_FRAMEBUFFER, fbNeighborPush);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, neighbor, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depNeighborPush, 0);
	fberrorecho();
	
	glGenFramebuffers(1, &fbNeighborBlind);
	glBindFramebuffer(GL_FRAMEBUFFER, fbNeighborBlind);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, etc, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depNeighborBlind, 0);
	fberrorecho();
}

void FluidFB::init(
	unsigned int particleMax, 
	float h, 
	float physicalSpaceX, 
	float physicalSpaceY, 
	float physicalSpaceZ)
{
	//Position init
	std::vector<float> data;

	float sep = h * 0.5;
	float offset = h * 2.0;
	float sx, sy, sz;
	float x, y, z;

	sx = offset;
	sy = offset;
	sz = offset;

	x = sx;
	y = sy;
	z = sz;

	for (int i = 0; i < particleMax; i++) {
		data.push_back(x);
		data.push_back(y);
		data.push_back(z);
		x += sep;
		if (x > physicalSpaceX - offset) {
			x = sx;
			y += sep;
		}
		if (y > physicalSpaceY * 0.5 - offset) {
			y = sy;
			z += sep;
		}
		if (z > physicalSpaceZ - offset) {
			std::cerr << "Failed to initialize particle position" << std::endl;
			exit(1);
			return;
		}
	}

	glBindTexture(GL_TEXTURE_2D, pos);
	glTexImage2D(
		GL_TEXTURE_2D, 0,
		GL_RGB32F,
		particleSpaceW, particleSpaceH,  
		0, GL_RGB, GL_FLOAT, 
		&data[0]);

	data.clear();

	//Availablize
	for (int i = 0; i < particleMax; i++) {
		data.push_back(1.0);
		data.push_back(0.0);
	}

	glBindTexture(GL_TEXTURE_2D, etc);
	glTexImage2D(
		GL_TEXTURE_2D, 0,
		GL_RG32F,
		particleSpaceW, particleSpaceH,
		0, GL_RG, GL_FLOAT,
		&data[0]);

	data.clear();

	//Sprite
	shdSprite = glCreateProgram();
	loadShader(shdSprite, GL_VERTEX_SHADER, "sprite_v.glsl");
	loadShader(shdSprite, GL_GEOMETRY_SHADER, "sprite_g.glsl");
	loadShader(shdSprite, GL_FRAGMENT_SHADER, "sprite_f.glsl");
	linkProgram(shdSprite);

	glUseProgram(shdSprite);
	glUniform1i(glGetUniformLocation(shdSprite, "tex"), 0);
	uniSPmatModelView = glGetUniformLocation(shdSprite, "matModelView");
	uniSPmatProjection = glGetUniformLocation(shdSprite, "matProjection");
	uniSPwidth = glGetUniformLocation(shdSprite, "width");
	uniSPheight = glGetUniformLocation(shdSprite, "height");
	uniSPbias = glGetUniformLocation(shdSprite, "bias");
	uniSPscale = glGetUniformLocation(shdSprite, "scale");

	glGenBuffers(1, &vboZeropoint);
	glBindBuffer(GL_ARRAY_BUFFER, vboZeropoint);
	data.push_back(0.0);
	data.push_back(0.0);
	data.push_back(0.0);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
	data.clear();

	errorecho("FB init");
}

void FluidFB::drawBuffer(GLuint buffer, float x, float y, float scale, float bias) {
	mat4 modelview, projection;

	glUseProgram(shdSprite);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, buffer);

	modelview = Matrix::Translate(vec4(x, y, 0.0, 0.0));
	glUniformMatrix4fv(uniSPmatModelView, 1, GL_TRUE, modelview);
	glUniformMatrix4fv(uniSPmatProjection, 1, GL_TRUE, projection);
	glUniform1f(uniSPscale, scale);
	glUniform1f(uniSPbias, bias);

	glBindBuffer(GL_ARRAY_BUFFER, vboZeropoint);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawArrays(GL_POINTS, 0, 1);
	glDisableVertexAttribArray(0);
}

void FluidFB::debugdraw() {
	drawBuffer(pos, -0.75, 0.75, 1.3, 0.0);
	drawBuffer(vel, -0.45, 0.75, 2.0, 0.5);
	drawBuffer(prop, -0.15, 0.75, 0.0006, 0.5);
	drawBuffer(etc, 0.15, 0.75, 1.0, 0.0);
	drawBuffer(neighbor, 0.55, 0.75, 1.0, 0.0);
}

static void swapi(GLuint& i, GLuint& j) {
	GLuint temp;
	temp = i;
	i = j;
	j = temp;
}

void FluidFB::swap() {
	swapi(pos, posback);
	swapi(vel, velback);
	swapi(depPhysicalStepPost, depPhysicalStepPostBack);
	swapi(fbPhysicalStepPost, fbPhysicalStepPostBack);
}

void FluidFB::bind() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, pos);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, vel);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, prop);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, etc);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, neighbor);
}