//
// AcornBusTwoRideEachTaste 2016.06.09
// Shader management (originated from Angel)
//

#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>

void loadShader(GLuint program, GLenum type, const char* fn);
void linkProgram(GLuint program);