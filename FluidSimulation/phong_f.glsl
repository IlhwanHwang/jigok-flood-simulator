#version 330

in vec2 fTex;
in vec4 fPos;
in vec3 fNorm;
in mat3 fTBN;

uniform sampler2D tex;
uniform sampler2D norm;
uniform vec3 light;
uniform vec3 lightEye;

layout (location = 0) out vec4 pCol;

void main() {
	vec3 sN = texture(norm, fTex).xyz * 2.0 - 1.0;
	vec3 N = normalize(fTBN * sN);

	vec3 L = light;
	vec3 R = reflect(L, N);
	vec3 V = normalize(lightEye - fPos.xyz);

	float I = max(dot(L, N), 0.0);
	float S = pow(max(-dot(V, R), 0.0), 16.0) * 1.0;

	vec4 samplePoint = texture(tex, fTex);

	pCol = vec4(samplePoint.rgb * I + S, samplePoint.a);
}