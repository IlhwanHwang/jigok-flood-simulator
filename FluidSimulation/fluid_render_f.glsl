#version 330

in vec2 fTex;
in vec2 fpid;

uniform sampler2D mapProp;
uniform sampler2D tex;
uniform sampler2D mapColor;

layout (location = 0) out vec4 pCol;

void main() {
	vec2 prop = texture2D(mapProp, fpid).rg;
	pCol = texture2D(tex, fTex);
	if (pCol.a < 0.5)
		discard;
	pCol *= texture2D(mapColor, vec2(clamp(-prop.y * 0.0002 + 0.8, 0.01, 0.99), 0.0));
}