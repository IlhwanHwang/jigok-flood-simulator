#version 330

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

out vec2 fTex;

void main() {
	gl_Position = vec4(-1.0, -1.0, 0.0, 1.0);
	fTex = vec2(0.0, 0.0);
	EmitVertex();

	gl_Position = vec4(1.0, -1.0, 0.0, 1.0);
	fTex = vec2(1.0, 0.0);
	EmitVertex();

	gl_Position = vec4(-1.0, 1.0, 0.0, 1.0);
	fTex = vec2(0.0, 1.0);
	EmitVertex();

	gl_Position = vec4(1.0, 1.0, 0.0, 1.0);
	fTex = vec2(1.0, 1.0);
	EmitVertex();

	EndPrimitive();
}