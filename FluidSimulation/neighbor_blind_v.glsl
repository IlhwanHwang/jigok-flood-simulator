#version 330

layout (location = 0) in vec2 nid;

uniform float stageNormf;

#include "map.glsl"

void main() {
	vec3 nsample = texture2D(mapNeighbor, nid + vec2(0.0, stageNormf)).xyz;
	vec2 pid = nsample.xy;
	float available = nsample.z;

	gl_Position.xy = pid * 2.0 - 1.0;
	gl_Position.z = 1.5 - available;
	gl_Position.w = 1.0;
}