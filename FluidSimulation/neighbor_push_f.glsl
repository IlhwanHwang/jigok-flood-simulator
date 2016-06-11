#version 330

in vec2 fpid;

layout (location = 0) out vec3 neighbor;

void main() {
	neighbor.rg = fpid;
	neighbor.b = 1.0;
}