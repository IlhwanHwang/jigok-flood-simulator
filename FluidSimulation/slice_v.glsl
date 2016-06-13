#version 330

layout (location = 0) in vec4 vPos;
layout (location = 1) in vec2 vTex;
layout (location = 2) in vec3 vNorm;

uniform float layer;
uniform float scale;
uniform mat4 matFit;
uniform mat4 matModelView;

out vec3 gNorm;

void main() {
	gl_Position = matFit * matModelView * vPos;
	gl_Position.z *= scale;
	gl_Position.z -= (layer - 0.5 * scale) * 2.0;

	vec4 norm = matModelView * vec4(vNorm, 0.0);
	gNorm = normalize(norm.xyz);
}