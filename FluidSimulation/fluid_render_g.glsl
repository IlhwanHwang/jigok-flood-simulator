#version 330

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform float pRadius = 5.0;

in vec2 gpid[];
out vec2 fTex;
out vec2 fpid;

void main() {
	gl_Position = gl_in[0].gl_Position + vec4(-pRadius, -pRadius, 0.0, 0.0);
	fTex = vec2(0.0, 0.0);
	fpid = gpid[0];
	EmitVertex();

	gl_Position = gl_in[0].gl_Position + vec4(pRadius, -pRadius, 0.0, 0.0);
	fTex = vec2(1.0, 0.0);
	fpid = gpid[0];
	EmitVertex();

	gl_Position = gl_in[0].gl_Position + vec4(-pRadius, pRadius, 0.0, 0.0);
	fTex = vec2(0.0, 1.0);
	fpid = gpid[0];
	EmitVertex();

	gl_Position = gl_in[0].gl_Position + vec4(pRadius, pRadius, 0.0, 0.0);
	fTex = vec2(1.0, 1.0);
	fpid = gpid[0];
	EmitVertex();

	EndPrimitive();
}