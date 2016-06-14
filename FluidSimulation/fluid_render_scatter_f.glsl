#version 330

in vec2 fTex;
in vec2 fpid;

uniform sampler2D tex;
uniform sampler2D mapVelocity;

layout (location = 0) out vec4 scatter;

void main() {
	vec4 col = texture(tex, fTex);
	float vel = length(texture(mapVelocity, fpid).rgb);
	float dis = (noise1(gl_FragCoord.x + gl_FragCoord.y + gl_FragCoord.z) * 0.5 + 0.5);
	scatter.rgb = dis * vel * vec3(1.0, 1.0, 1.0) * col.a * 0.01;
	scatter.a = 1.0;
}