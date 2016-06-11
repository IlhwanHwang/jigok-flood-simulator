#version 330

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform float width = 0.25;
uniform float height = 0.25;

out vec2 fTex;

void main() {
	gl_Position = gl_in[0].gl_Position + vec4(-width / 2.0, -height / 2.0, 0.0, 0.0);
	fTex = vec2(0.0, 0.0);
	EmitVertex();

	gl_Position = gl_in[0].gl_Position + vec4(width / 2.0, -height / 2.0, 0.0, 0.0);
	fTex = vec2(1.0, 0.0);
	EmitVertex();

	gl_Position = gl_in[0].gl_Position + vec4(-width / 2.0, height / 2.0, 0.0, 0.0);
	fTex = vec2(0.0, 1.0);
	EmitVertex();

	gl_Position = gl_in[0].gl_Position + vec4(width / 2.0, height / 2.0, 0.0, 0.0);
	fTex = vec2(1.0, 1.0);
	EmitVertex();

	EndPrimitive();
}