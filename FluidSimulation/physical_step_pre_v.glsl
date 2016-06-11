#version 330

layout (location = 0) in vec2 pid;

#include "map.glsl"

out vec2 fpid;

void main() {
	vec2 etc = texture2D(mapETC, pid).xy;
	float available = etc.x;

	gl_Position.xy = pid * 2.0 - 1.0;
	gl_Position.z = 1.5 - available; //Clip out when not available or located
	gl_Position.w = 1.0;

	fpid = pid;
}