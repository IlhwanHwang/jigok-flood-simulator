#version 330

layout (location = 0) in vec4 vPos;
layout (location = 1) in vec2 vTex;
layout (location = 2) in vec3 vNorm;

uniform mat4 matProjection;
uniform mat4 matModelView;

out vec3 fNorm;

void main() {
	gl_Position = matProjection * matModelView * vPos / vPos.w;
	vec4 norm = matModelView * vec4(vNorm, 0.0);
	fNorm = normalize(norm.xyz);
}