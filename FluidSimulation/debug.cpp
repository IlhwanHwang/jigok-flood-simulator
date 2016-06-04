//
// AcornBusTwoRideEachTaste 2016.06.03
// Debug output
//

#include "debug.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

using namespace std;

void errorecho(const char* append) {
	cout << append << ": ";
	switch (glGetError()) {
	case GL_NO_ERROR:
		cout << "No error" << endl;
		break;
	case GL_INVALID_ENUM:
		cout << "Invaild enumerator" << endl;
		break;
	case GL_INVALID_VALUE:
		cout << "Invalid value" << endl;
		break;
	case GL_INVALID_OPERATION:
		cout << "Invalid operation" << endl;
		break;
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		cout << "Invalid framebuffer operation" << endl;
		break;
	case GL_OUT_OF_MEMORY:
		cout << "Out of memory" << endl;
		break;
	}
}

void errorecho() {
	errorecho("Error");
}

void fberrorecho() {
	cout << "FB:: ";

	switch (glCheckFramebufferStatus(GL_FRAMEBUFFER)) {
	case GL_FRAMEBUFFER_COMPLETE:
		cout << "Framebuffer initialized." << endl;
		break;
	case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
		cout << "Framebuffer attachment incompleted." << endl;
		break;
	case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
		cout << "No image is attached to framebuffer." << endl;
		break;
	case GL_FRAMEBUFFER_UNSUPPORTED:
		cout << "Framebuffer is unsupported." << endl;
		break;
	}
}