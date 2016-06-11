#version 330

layout (location = 0) out vec4 pCol;

uniform mat4 matModelView;
uniform mat4 matProjection;

void main() {
	pCol = vec4(0.5, 0.5, 0.5, 1.0);
}