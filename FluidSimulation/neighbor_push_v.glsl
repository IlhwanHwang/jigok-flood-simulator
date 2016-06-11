#version 330

layout (location = 0) in vec2 pid;

#include "map.glsl"

uniform float stagef;

out vec2 fpid;

#include "neighbor_grid.glsl"

void main() {
	vec3 pos = texture2D(mapPosition, pid).xyz;
	vec2 etc = texture2D(mapETC, pid).xy;
	float available = etc.x;
	float nlocated = etc.y;
	vec3 grid = pos2grid(pos);

	gl_Position.xy = grid2nid(grid, stagef) * 2.0 - 1.0;
	gl_Position.z = 1.5 - available + nlocated; //Clip out when not available or located
	gl_Position.w = 1.0;

	fpid = pid;
}