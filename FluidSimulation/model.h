//
// BetterCarryingEachOther 2016.04.01
// model structure
//

#pragma once

#include <vector>
#include <GL/glew.h>

#include "vec.h"

using namespace std;

struct vertex {
	vec3 pos;
	vec2 tex;
	vec3 norm;

	vertex() {}

	vertex(const vec3 &pos, const vec2 &tex, const vec3 &norm)
		: pos(pos), tex(tex), norm(norm) {}
};

class Model {
public:
	GLuint buffer;
	GLuint size;
	vector<vertex> vertices;

public:

	Model();

	void addPoint(vec3 pos, vec2 tex, vec3 norm);
	void addPoint(vertex v);
	void load(const char* fn);
	void load(const char* fn, const char* group);
	void generate();
	void draw();
};