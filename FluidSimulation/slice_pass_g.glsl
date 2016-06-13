#version 330

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 gNorm[];
out vec3 fNorm;

void main() {
	gl_Position = gl_in[0].gl_Position;
	fNorm = gNorm[0];
	EmitVertex();

	gl_Position = gl_in[1].gl_Position;
	fNorm = gNorm[1];
	EmitVertex();

	gl_Position = gl_in[2].gl_Position;
	fNorm = gNorm[2];
	EmitVertex();

	EndPrimitive();
}