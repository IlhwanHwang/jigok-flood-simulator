#version 330

in vec3 fTex;

uniform sampler3D env;

layout (location = 0) out vec4 fCol;

void main() {
	fCol = texture(env, fTex);
	if (abs(fCol.r) + abs(fCol.g) + abs(fCol.b) <= 0.0)
		discard;
	fCol.rgb = normalize(fCol.rgb);
	fCol.rgb = fCol.rgb * 0.5 + 0.5;
}