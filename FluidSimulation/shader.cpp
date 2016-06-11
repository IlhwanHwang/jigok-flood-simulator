//
// AcornBusTwoRideEachTaste 2016.06.09
// Shader management (originated from Angel)
//

#include <iostream>
#include <fstream>
#include <string>

#include <GL/glew.h>
#include <GL/freeglut.h>

static std::string file2string(std::string fn) {
	std::ifstream f(fn);
	std::string str;
	std::string buf;

	if (!f.is_open()) {
		std::cerr << "Failed to read " << fn << std::endl;
		exit(EXIT_FAILURE);
	}

	while (!f.eof()) {
		std::getline(f, buf);
		str += buf + "\n";
	}

	return str;
}

void loadShader(GLuint program, GLenum type, const char* fn) {
	std::string buf;
	std::string source;
	std::ifstream f(fn);

	if (!f.is_open()) {
		std::cerr << "Failed to read " << fn << std::endl;
		exit(EXIT_FAILURE);
	}

	while (!f.eof()) {
		std::getline(f, buf);
		if (buf.find("#include") == 0) {
			size_t pos1 = buf.find_first_of("\"");
			size_t pos2 = buf.find_last_of("\"");
			buf = file2string(buf.substr(pos1 + 1, pos2 - pos1 - 1));
		}
		source += buf + "\n";
	}

	const char* csource = source.c_str();

	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, (const GLchar**)&csource, NULL);
	glCompileShader(shader);

	GLint  compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		std::cerr << fn << " failed to compile:" << std::endl;
		GLint  logSize;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
		char* logMsg = new char[logSize];
		glGetShaderInfoLog(shader, logSize, NULL, logMsg);
		std::cerr << logMsg << std::endl;
		delete[] logMsg;

		exit(EXIT_FAILURE);
	}

	glAttachShader(program, shader);
}

void linkProgram(GLuint program) {
	glLinkProgram(program);

	GLint  linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (!linked) {
		std::cerr << "Shader program failed to link" << std::endl;
		GLint  logSize;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
		char* logMsg = new char[logSize];
		glGetProgramInfoLog(program, logSize, NULL, logMsg);
		std::cerr << logMsg << std::endl;
		delete[] logMsg;

		exit(EXIT_FAILURE);
	}

	glUseProgram(program);
}