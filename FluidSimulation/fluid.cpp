//
// AcornBusTwoRideEachTaste 2016.06.04
// Fluid simulation (core)
//

#include "fluid.h"
#include "shader.h"
#include "debug.h"

#include <vector>
#include <iostream>

#include "mat.h"

Fluid::Fluid() :
	particleSpaceW	(256), 
	particleSpaceH	(256), 
	particleMax		(particleSpaceW * particleSpaceH),

	h	(0.0457),

	physicalSpaceX	(0.8),
	physicalSpaceY	(2.0),
	physicalSpaceZ	(2.0),

	neighborCellSizeX	(physicalSpaceX / floor(physicalSpaceX / h)),
	neighborCellSizeY	(physicalSpaceY / floor(physicalSpaceY / h)),
	neighborCellSizeZ	(physicalSpaceZ / floor(physicalSpaceZ / h)),

	neighborCellNumX	((unsigned int)(physicalSpaceX / neighborCellSizeX)),
	neighborCellNumY	((unsigned int)(physicalSpaceY / neighborCellSizeY)),
	neighborCellNumZ	((unsigned int)(physicalSpaceZ / neighborCellSizeZ)),
	neighborCellLength	(32),

	neighborSpaceW(neighborCellNumX * neighborCellNumZ),
	neighborSpaceH(neighborCellNumY * neighborCellLength)
{
	std::cout << "particleSpaceW: " << particleSpaceW << std::endl;
	std::cout << "particleSpaceH: " << particleSpaceH << std::endl;
	std::cout << "neighborSpaceW: " << neighborSpaceW << std::endl;
	std::cout << "neighborSpaceH: " << neighborSpaceH << std::endl;
	std::cout << "neighborCellNumX: " << neighborCellNumX << std::endl;
	std::cout << "neighborCellNumY: " << neighborCellNumY << std::endl;
	std::cout << "neighborCellNumZ: " << neighborCellNumZ << std::endl;
}

void Fluid::init() {
	errorecho("Flush Init");

	//VAO
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//Framebuffer
	fb = FluidFB(particleSpaceW, particleSpaceH, neighborSpaceW, neighborSpaceH);
	fb.generate();
	fb.init(particleMax, h, physicalSpaceX, physicalSpaceY, physicalSpaceZ);

	//VBOs
	std::vector<float> data;

	std::cout << "Initializing vboParticleForEach..." << std::endl;
	for (int i = 0; i < particleSpaceW; i++) {
		for (int j = 0; j < particleSpaceH; j++) {
			data.push_back((i + 0.5) / particleSpaceW);
			data.push_back((j + 0.5) / particleSpaceH);
		}
	}
	glGenBuffers(1, &vboParticleForEach);
	glBindBuffer(GL_ARRAY_BUFFER, vboParticleForEach);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
	data.clear();
	errorecho("vboParticleForEach");

	std::cout << "Initializing vboNeighborForEach..." << std::endl;
	for (int i = 0; i < neighborSpaceW; i++) {
		for (int j = 0; j < neighborCellNumY; j++) {
			data.push_back((i + 0.5) / neighborSpaceW);
			data.push_back((j + 0.5) / neighborSpaceH);
		}
	}
	glGenBuffers(1, &vboNeighborForEach);
	glBindBuffer(GL_ARRAY_BUFFER, vboNeighborForEach);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
	data.clear();
	errorecho("vboNeighborForEach");

	std::cout << "Fluid initiation complete" << std::endl;

	//UI
	ui.init(physicalSpaceX, physicalSpaceY, physicalSpaceZ);

	//Neighbor Push
	shdNeighborPush = glCreateProgram();
	loadShader(shdNeighborPush, GL_VERTEX_SHADER, "neighbor_push_v.glsl");
	loadShader(shdNeighborPush, GL_FRAGMENT_SHADER, "neighbor_push_f.glsl");
	linkProgram(shdNeighborPush);
	uniNPstagef = glGetUniformLocation(shdNeighborPush, "stagef");
	uniformNeighborGrid(shdNeighborPush);
	uniformMap(shdNeighborPush);

	//Neighbor Blind
	shdNeighborBlind = glCreateProgram();
	loadShader(shdNeighborBlind, GL_VERTEX_SHADER, "neighbor_blind_v.glsl");
	loadShader(shdNeighborBlind, GL_FRAGMENT_SHADER, "neighbor_blind_f.glsl");
	linkProgram(shdNeighborBlind);
	uniNBstageNormf = glGetUniformLocation(shdNeighborBlind, "stageNormf");
	uniformMap(shdNeighborBlind);

	//Physical Step Pre
	shdPhysicalStepPre = glCreateProgram();
	loadShader(shdPhysicalStepPre, GL_VERTEX_SHADER, "physical_step_pre_v.glsl");
	loadShader(shdPhysicalStepPre, GL_FRAGMENT_SHADER, "physical_step_pre_f.glsl");
	linkProgram(shdPhysicalStepPre);
	uniformNeighborGrid(shdPhysicalStepPre);
	uniformMap(shdPhysicalStepPre);

	//Physical Step Post
	shdPhysicalStepPost = glCreateProgram();
	loadShader(shdPhysicalStepPost, GL_VERTEX_SHADER, "physical_step_post_v.glsl");
	loadShader(shdPhysicalStepPost, GL_FRAGMENT_SHADER, "physical_step_post_f.glsl");
	linkProgram(shdPhysicalStepPost);
	glUniform1i(glGetUniformLocation(shdPhysicalStepPost, "mapPosition"), 0);
	glUniform1i(glGetUniformLocation(shdPhysicalStepPost, "mapVelocity"), 1);
	glUniform1i(glGetUniformLocation(shdPhysicalStepPost, "mapProp"), 2);
	glUniform1i(glGetUniformLocation(shdPhysicalStepPost, "mapETC"), 3);
	glUniform1i(glGetUniformLocation(shdPhysicalStepPost, "mapNeighbor"), 4);
	uniformNeighborGrid(shdPhysicalStepPost);
	uniformMap(shdPhysicalStepPost);
	uniformPhysical(shdPhysicalStepPost);

	errorecho("Shaders");
}

void Fluid::uniformNeighborGrid(GLuint program) {
	glUseProgram(program);
	glUniform1f(glGetUniformLocation(program, "neighborCellSizeX"), (float)neighborCellSizeX);
	glUniform1f(glGetUniformLocation(program, "neighborCellSizeY"), (float)neighborCellSizeY);
	glUniform1f(glGetUniformLocation(program, "neighborCellSizeZ"), (float)neighborCellSizeZ);
	glUniform1f(glGetUniformLocation(program, "neighborCellNumX"), (float)neighborCellNumX);
	glUniform1f(glGetUniformLocation(program, "neighborCellNumY"), (float)neighborCellNumY);
	glUniform1f(glGetUniformLocation(program, "neighborCellNumZ"), (float)neighborCellNumZ);
	glUniform1f(glGetUniformLocation(program, "neighborCellLength"), (float)neighborCellLength);
}

void Fluid::uniformMap(GLuint program) {
	glUseProgram(program);
	glUniform1i(glGetUniformLocation(program, "mapPosition"), 0);
	glUniform1i(glGetUniformLocation(program, "mapVelocity"), 1);
	glUniform1i(glGetUniformLocation(program, "mapProp"), 2);
	glUniform1i(glGetUniformLocation(program, "mapETC"), 3);
	glUniform1i(glGetUniformLocation(program, "mapNeighbor"), 4);
	glUniform2f(glGetUniformLocation(program, "particleSpaceOffset"), 0.5 / particleSpaceW, 0.5 / particleSpaceH);
	glUniform2f(glGetUniformLocation(program, "neighborSpaceOffset"), 0.5 / neighborSpaceW, 0.5 / neighborSpaceH);
}

void Fluid::uniformPhysical(GLuint program) {
	glUseProgram(program);
	glUniform1f(glGetUniformLocation(program, "physicalDeltaTime"), 0.002);
	glUniform1f(glGetUniformLocation(program, "physicalSpaceX"), physicalSpaceX);
	glUniform1f(glGetUniformLocation(program, "physicalSpaceY"), physicalSpaceY);
	glUniform1f(glGetUniformLocation(program, "physicalSpaceZ"), physicalSpaceZ);
}

void Fluid::draw() {
	glViewport(0, 0, 1920, 1920);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ui.draw(
		vboParticleForEach,
		particleMax,
		fb.mapPosition(),
		fb.mapVelocity(),
		fb.mapETC());

	glClear(GL_DEPTH_BUFFER_BIT);

	fb.debugdraw();

	glutSwapBuffers();
}

void Fluid::update() {
	fb.outputNeighborPush();
	glClearColor(0.0, 0.0, 0.0, 0.0); //Blue 0.0 is unavailable
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	fb.outputNeighborBlind();
	glClearColor(0.0, 0.0, 0.0, 0.0); //Green 0.0 is unlocated
	glClearDepth(1.0);
	glColorMask(GL_FALSE, GL_TRUE, GL_FALSE, GL_FALSE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	for (int i = 0; i < neighborCellLength; i++) {
		//Neighbor Push
		fb.outputNeighborPush();
		glUseProgram(shdNeighborPush);
		glUniform1f(uniNPstagef, (float)i);
		fb.bind();
		glClear(GL_DEPTH_BUFFER_BIT);
		glBindBuffer(GL_ARRAY_BUFFER, vboParticleForEach);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glDrawArrays(GL_POINTS, 0, particleMax);
		glDisableVertexAttribArray(0);

		//Neighbor Blind
		fb.outputNeighborBlind();
		glUseProgram(shdNeighborBlind);
		glUniform1f(uniNBstageNormf, (float)i / neighborCellLength);
		fb.bind();
		glClear(GL_DEPTH_BUFFER_BIT);
		glBindBuffer(GL_ARRAY_BUFFER, vboNeighborForEach);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glDrawArrays(GL_POINTS, 0, neighborCellNumX * neighborCellNumY * neighborCellNumZ);
		glDisableVertexAttribArray(0);
	}
	
	//Physical Step Pre
	fb.outputPhysicalStepPre();
	glUseProgram(shdPhysicalStepPre);
	fb.bind();
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindBuffer(GL_ARRAY_BUFFER, vboParticleForEach);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawArrays(GL_POINTS, 0, particleMax);
	glDisableVertexAttribArray(0);
	
	//Physical Step Post
	fb.outputPhysicalStepPost();
	glUseProgram(shdPhysicalStepPost);
	fb.bind();
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindBuffer(GL_ARRAY_BUFFER, vboParticleForEach);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawArrays(GL_POINTS, 0, particleMax);
	glDisableVertexAttribArray(0);
	
	fb.swap();
}