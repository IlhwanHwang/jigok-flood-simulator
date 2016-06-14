#version 330

in vec2 fTex;

uniform sampler2D tex;
uniform sampler2D dep;
uniform float depOffset;

layout (location = 0) out vec4 pCol;

void main() {
	pCol = texture(tex, fTex);
	if (pCol.a < 0.5)
		discard;
	gl_FragDepth = texture(dep, fTex).r + depOffset;
}