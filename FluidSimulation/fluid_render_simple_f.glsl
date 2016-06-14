#version 330

in vec2 fTex;
in vec2 fpid;
in float fDepth;

uniform sampler2D mapProp;
uniform sampler2D tex;
uniform sampler2D mapColor;
uniform sampler2D mapNorm;

layout (location = 0) out vec4 pCol;

void main() {
	pCol = texture2D(tex, fTex);
	if (pCol.a < 0.5)
		discard;
	vec2 prop = texture(mapProp, fpid).rg;
	pCol.rgb = texture(mapColor, vec2(clamp(0.8 - prop.g * 0.0003, 0.01, 0.99), 0.0)).rgb;
}