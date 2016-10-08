#version 330

layout (location = 0) in vec2 pid;

uniform sampler2D mapPosition;
uniform sampler2D mapETC;

uniform mat4 matModelView;
uniform mat4 matProjection;

out vec2 gpid;

void main() {
	vec3 pos = texture2D(mapPosition, pid).xyz;
	vec2 etc = texture2D(mapETC, pid).xy;
	float available = etc.x;

	gl_Position = matProjection * matModelView * vec4(pos, 1.0);
	gl_Position.w *= available; //Clip out when not available
	gpid = pid;
}