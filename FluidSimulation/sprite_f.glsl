#version 330

in vec2 fTex;

uniform sampler2D tex;
uniform float bias;
uniform float scale;

layout (location = 0) out vec4 pCol;

void main() {
	pCol = texture2D(tex, fTex);
	pCol *= scale;
	pCol += bias;
}