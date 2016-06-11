//
// BetterCarryingEachOther 2016.04.07
// texture management unit
//

#pragma once

#include <GL/glut.h>

class Texture {
private:
	unsigned w, h;
	GLuint buf;

public:
	void push(GLsizei w, GLsizei h, const unsigned char* data);
	void load(const char* fn);
	void bind() { glBindTexture(GL_TEXTURE_2D, buf); }
	GLuint tex() { return buf; }
};