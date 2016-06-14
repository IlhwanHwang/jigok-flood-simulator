#version 330

in vec2 fTex;
in vec2 fpid;

uniform sampler2D tex;

layout (location = 0) out vec4 asorb;

void main() {
	vec4 col = texture(tex, fTex);
	asorb = vec4(0.02, 0.005, 0.001, 0.1) * col.a;
}