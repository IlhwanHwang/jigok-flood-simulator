#version 330

layout (location = 0) in vec4 vPos;

uniform mat4 matModelView;
uniform mat4 matProjection;

void main() {
	gl_Position = matProjection * matModelView * vPos / vPos.w;
}