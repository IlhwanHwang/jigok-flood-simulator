#version 330

in vec2 fTex;

uniform sampler2D normal;

uniform vec3 light;

layout (location = 0) out vec4 pCol;

void main() {
	vec4 nsample = texture(normal, fTex);
	if (nsample.a < 0.5)
		discard;

	vec3 N = nsample.xyz;
	N *= 2.0;
	N -= 1.0;
	N = normalize(N);

	vec3 V = vec3(0.0, 0.0, -1.0);
	vec3 R = reflect(light, N);
	float S = pow(max(0.0, dot(V, R)), 8.0);

	pCol += vec4(vec3(S, S, S) * 1.0, 1.0);
}