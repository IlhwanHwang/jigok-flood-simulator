#version 330

in vec3 fNorm;

layout (location = 0) out vec4 env;

void main() {
	env.xyz = normalize(fNorm);
}