#version 330

layout (location = 0) in vec2 pid;

#include "map.glsl"

uniform mat4 matModelView;
uniform mat4 matProjection;

out vec2 gpid;

void main() {
	vec3 pos = texture2D(mapPosition, pid).xyz;
	gl_Position = matProjection * matModelView * vec4(pos, 1.0);
	gpid = pid;
}