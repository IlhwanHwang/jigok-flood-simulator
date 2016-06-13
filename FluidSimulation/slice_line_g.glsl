#version 330

layout (triangles) in;
layout (line_strip, max_vertices = 2) out;

in vec3 gNorm[];
out vec3 fNorm;

vec2 lerp(vec2 a, vec2 b, float x) {
	return (1.0 - x) * a + x * b;
}

vec3 lerp(vec3 a, vec3 b, float x) {
	return (1.0 - x) * a + x * b;
}

void main() {
	float parity01 = sign(gl_in[0].gl_Position.z * gl_in[1].gl_Position.z);
	float parity12 = sign(gl_in[1].gl_Position.z * gl_in[2].gl_Position.z);
	float parity20 = sign(gl_in[2].gl_Position.z * gl_in[0].gl_Position.z);

	if (abs(gl_in[0].gl_Position.z) > 1.0 && 
		abs(gl_in[1].gl_Position.z) > 1.0 && 
		abs(gl_in[2].gl_Position.z) > 1.0 &&
		parity01 == parity12) {
		EndPrimitive();
		return;
	}

	int ind[3];

	if (parity01 < 0.0 && parity12 < 0.0) {
		ind[0] = 0;
		ind[1] = 1;
		ind[2] = 2;
	}
	else if (parity12 < 0.0 && parity20 < 0.0) {
		ind[0] = 1;
		ind[1] = 2;
		ind[2] = 0;
	}
	else if (parity20 < 0.0 && parity01 < 0.0) {
		ind[0] = 2;
		ind[1] = 0;
		ind[2] = 1;
	}
	else {
		EndPrimitive();
		return;
	}
	
	vec4 pos[3];

	for (int i = 0; i < 3; i++) {
		pos[i] = gl_in[ind[i]].gl_Position;
	}

	float phase1 = abs(pos[0].z / (pos[0].z - pos[1].z));
	float phase2 = abs(pos[1].z / (pos[1].z - pos[2].z));
	
	gl_Position = vec4(lerp(pos[0].xy, pos[1].xy, phase1), 0.0, 1.0);
	fNorm = lerp(gNorm[ind[0]], gNorm[ind[1]], phase1);
	EmitVertex();

	gl_Position = vec4(lerp(pos[1].xy, pos[2].xy, phase2), 0.0, 1.0);
	fNorm = lerp(gNorm[ind[1]], gNorm[ind[2]], phase2);
	EmitVertex();

	EndPrimitive();
}