#version 330

layout (location = 0) in vec4 vPos;
layout (location = 1) in vec2 vTex;
layout (location = 2) in vec3 vNorm;

uniform float depth;
uniform float scale;
uniform mat4 matModelView;

out vec3 fNorm;

void main() {
	gl_Position = matModelView * vPos;
	gl_Position *= scale;
	gl_Position += depth;

	vec4 norm = matModelView * vec4(vNorm, 0.0);
	fNorm = norm.xyz;
}