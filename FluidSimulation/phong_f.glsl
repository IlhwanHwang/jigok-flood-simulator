#version 330

in vec3 fNorm;

layout (location = 0) out vec4 diffuse;

void main() {
	diffuse.xyz = fNorm * 0.5 + 0.5;
	diffuse.a = 1.0;
}