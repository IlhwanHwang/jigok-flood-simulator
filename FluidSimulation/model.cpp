//
// AcornBusTwoRideEachTaste 2016.06.12
// model structure
//

#include <GL/glew.h>
#include <fstream>
#include <string>

#include "model.h"
#include "shader.h"
#include "debug.h"

static vector<string> tokenize(string str, string delim) {
	vector<string> v;
	size_t seek = 0;

	while (str.length() > seek) {
		size_t pos;
		pos = str.find_first_of(delim, seek);

		if (pos != string::npos) {
			v.push_back(str.substr(seek, pos - seek));
			seek = pos + 1;
		}
		else {
			v.push_back(str.substr(seek));
			seek = str.length();
		}
	}

	return v;
}

Model::Model() {}

void Model::addPoint(vec3 pos, vec2 tex, vec3 norm) {
	vertices.push_back(vertex(pos, tex, norm));
}

void Model::addPoint(vertex v) {
	vertices.push_back(v);
}

void Model::load(const char* fn) {
	load(fn, NULL);
}

void Model::load(const char* fn, const char* group) {
	ifstream f(fn);

	vector<vec3> v;
	vector<vec2> vt;
	vector<vec3> vn;
	bool skip = true;

	v.push_back(vec3(0.0, 0.0, 0.0));
	vt.push_back(vec2(0.0, 0.0));
	vn.push_back(vec3(0.0, 0.0, 0.0));

	while (!f.eof()) {
		string buf;
		getline(f, buf);

		if (buf.length() == 0)
			continue;

		vector<string> t = tokenize(buf, " ");
		string flag = t[0];

		if (flag.compare("#") == 0) {
			continue;
		}
		else if (flag.compare("v") == 0) {
			v.push_back(vec3(stof(t[1]), stof(t[2]), stof(t[3])));
		}
		else if (flag.compare("vt") == 0) {
			vt.push_back(vec2(stof(t[1]), stof(t[2])));
		}
		else if (flag.compare("vn") == 0) {
			vn.push_back(vec3(stof(t[1]), stof(t[2]), stof(t[3])));
		}
		else if (flag.compare("g") == 0) {
			if (group != NULL) {
				if (skip) {
					if (string(group).compare(t[1]) == 0)
						skip = false;
					else
						continue;
				}
				else {
					break;
				}
			}
		}
		else if (flag.compare("f") == 0) {
			if (skip && group != NULL)
				continue;

			if (t.size() == 3)
				continue;

			bool quad = (t.size() == 5);

			vector<string> p1 = tokenize(t[1], "/");
			vector<string> p2 = tokenize(t[2], "/");
			vector<string> p3 = tokenize(t[3], "/");
			vector<string> p4;
			if (quad)
				p4 = tokenize(t[4], "/");

			vertex v1 = vertex(v[stoi(p1[0])], vt[stoi(p1[1])], vn[stoi(p1[2])]);
			vertex v2 = vertex(v[stoi(p2[0])], vt[stoi(p2[1])], vn[stoi(p2[2])]);
			vertex v3 = vertex(v[stoi(p3[0])], vt[stoi(p3[1])], vn[stoi(p3[2])]);
			vertex v4;
			if (quad)
				v4 = vertex(v[stoi(p4[0])], vt[stoi(p4[1])], vn[stoi(p4[2])]);

			addPoint(v1);
			addPoint(v2);
			addPoint(v3);
			if (quad) {
				addPoint(v3);
				addPoint(v4);
				addPoint(v1);
			}
		}
	}

	f.close();

	cout << "Model: " << fn << " loaded with " << vertices.size() << " vertices" << endl;
	generate();
}

void Model::generate() {
	size = vertices.size();

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(vertex), &vertices[0], GL_STATIC_DRAW);

	vertices.clear();
}

void Model::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid *)(sizeof(vec3)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid *)(sizeof(vec3) + sizeof(vec2)));
	glDrawArrays(GL_TRIANGLES, 0, size);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	//errorecho("Model drawing");
}