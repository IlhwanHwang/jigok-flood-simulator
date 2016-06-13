#version 330

layout (location = 0) in vec4 vPos;
layout (location = 1) in vec3 vTex;

uniform mat4 matProjection;
uniform mat4 matModelView;

out vec3 fTex;

void main() {
	gl_Position = matProjection * matModelView * vPos / vPos.w;
	fTex = vTex;
}