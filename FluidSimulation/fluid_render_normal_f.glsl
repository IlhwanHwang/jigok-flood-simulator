#version 330

in vec2 fTex;
in vec2 fpid;
in float fDepth;

uniform sampler2D mapProp;
uniform sampler2D tex;
uniform sampler2D mapColor;
uniform sampler2D mapNorm;

layout (location = 0) out vec4 norm;
layout (location = 1) out vec2 depth;

void main() {
	norm = texture2D(tex, fTex);
	if (norm.a < 0.5)
		discard;
	depth.r = gl_FragCoord.z;
}