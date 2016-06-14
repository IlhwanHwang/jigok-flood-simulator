#version 330

layout (location = 0) in vec4 vPos;
layout (location = 1) in vec2 vTex;
layout (location = 2) in vec3 vNorm;

uniform mat4 matProjection;
uniform mat4 matModelView;

out vec3 gNorm;
out vec2 gTex;
out vec4 gPos;

void main() {
	gPos = matModelView * vPos / vPos.w;
	gl_Position = matProjection * gPos;
	vec4 norm = matModelView * vec4(vNorm, 0.0);
	gNorm = normalize(norm.xyz);
	gTex = vTex;
}