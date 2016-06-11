#version 330

in vec2 fTex;
in vec2 fpid;

uniform sampler2D tex;

layout (location = 0) out vec4 pCol;

#include "map.glsl"

void main() {
	//pCol = texture2D(tex, fTex);
	//pCol = vec4(0.5, 0.5, 0.5, 1.0);

	pCol = texture2D(mapPosition, fpid);

	//if (pCol.a < 0.5)
	//	discard;
}