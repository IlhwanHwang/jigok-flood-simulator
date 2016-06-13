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

	envResolutionX = 256;
	envResolutionY = 256;
	envResolutionZ = 256;

	glGenTextures(1, &env);
	glBindTexture(GL_TEXTURE_3D, env);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB32F, envResolutionX, envResolutionY, envResolutionZ, 0, GL_RGB, GL_FLOAT, NULL);

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
		data.push_back(physicalSpaceZ - z);
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

void FluidFB::initEnv(
	Model& model, 
	mat4& matEnvModelview,
	float physicalSpaceX,
	float physicalSpaceY,
	float physicalSpaceZ) {
	GLuint fbTemp;
	GLuint tempDep;

	glGenTextures(1, &tempDep);
	glBindTexture(GL_TEXTURE_2D, tempDep);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, envResolutionX, envResolutionY, 0,
		GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);

	glGenFramebuffers(1, &fbTemp);
	glBindFramebuffer(GL_FRAMEBUFFER, fbTemp);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, tempDep, 0);

	GLuint shdSlice, shdSliceLine, uniLayer, uniLayerLine;
	shdSlice = glCreateProgram();
	loadShader(shdSlice, GL_VERTEX_SHADER, "slice_v.glsl");
	loadShader(shdSlice, GL_GEOMETRY_SHADER, "slice_pass_g.glsl");
	loadShader(shdSlice, GL_FRAGMENT_SHADER, "slice_f.glsl");
	linkProgram(shdSlice);
	glUseProgram(shdSlice);
	uniLayer = glGetUniformLocation(shdSlice, "layer");
	glUniform1f(glGetUniformLocation(shdSlice, "scale"), (float)envResolutionZ);

	mat4 fit;
	fit = Matrix::Scale(1.0 / physicalSpaceX, 1.0 / physicalSpaceY, 1.0 / physicalSpaceZ);
	glUniformMatrix4fv(glGetUniformLocation(shdSlice, "matFit"), 1, GL_TRUE, fit);
	glUniformMatrix4fv(glGetUniformLocation(shdSlice, "matModelView"), 1, GL_TRUE, matEnvModelview);

	shdSliceLine = glCreateProgram();
	loadShader(shdSliceLine, GL_VERTEX_SHADER, "slice_v.glsl");
	loadShader(shdSliceLine, GL_GEOMETRY_SHADER, "slice_line_g.glsl");
	loadShader(shdSliceLine, GL_FRAGMENT_SHADER, "slice_f.glsl");
	linkProgram(shdSliceLine);
	glUseProgram(shdSliceLine);

	uniLayerLine = glGetUniformLocation(shdSliceLine, "layer");
	glUniform1f(glGetUniformLocation(shdSliceLine, "scale"), (float)envResolutionZ);

	glUniformMatrix4fv(glGetUniformLocation(shdSliceLine, "matFit"), 1, GL_TRUE, fit);
	glUniformMatrix4fv(glGetUniformLocation(shdSliceLine, "matModelView"), 1, GL_TRUE, matEnvModelview);

	std::cout << "Building environment information" << std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, fbTemp);
	glViewport(0, 0, envResolutionX, envResolutionY);
	for (int i = 0; i < envResolutionZ; i++) {
		glFramebufferTexture3D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_3D, env, 0, i);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shdSlice);
		glUniform1f(uniLayer, (float)i);
		model.draw();
		
		glUseProgram(shdSliceLine);
		glUniform1f(uniLayerLine, (float)i);
		model.draw();
		
	}

	glDeleteProgram(shdSlice);
	glDeleteProgram(shdSliceLine);
	glDeleteFramebuffers(1, &fbTemp);
	glDeleteTextures(1, &tempDep);
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

	glUseProgram(0);
	
	glEnable(GL_TEXTURE_3D);
	glBindTexture(GL_TEXTURE_3D, env);
	glColor3f(1.0, 1.0, 1.0);

	for (float f = 0.0; f < 1.0; f += 0.1) {
		glBegin(GL_TRIANGLE_STRIP);
		glTexCoord3f(0.0, 0.0, f * 0.1 + 0.5);
		glVertex2f(-0.8 + f * 2.0, -0.7);
		glTexCoord3f(1.0, 0.0, f * 0.1 + 0.5);
		glVertex2f(-1.0 + f * 2.0, -0.7);
		glTexCoord3f(0.0, 1.0, f * 0.1 + 0.5);
		glVertex2f(-0.8 + f * 2.0, -0.9);
		glTexCoord3f(1.0, 1.0, f * 0.1 + 0.5);
		glVertex2f(-1.0 + f * 2.0, -0.9);
		glEnd();
	}

	glDisable(GL_TEXTURE_3D);
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
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_3D, env);
}