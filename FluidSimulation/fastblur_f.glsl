#version 330

#define KERNEL_WIDTH 4
#define KERNEL_WIDTH_F 4.0

in vec2 fTex;

uniform sampler2D tex;
uniform vec2 texel;

layout (location = 0) out vec4 pCol;

void main() {
	vec2 spInit = fTex - texel * vec2(KERNEL_WIDTH_F, KERNEL_WIDTH_F);
	vec2 sp = spInit;
	float samples = 0.0;

	if (texture(tex, fTex).a < 0.5)
		discard;

	for (int i = -KERNEL_WIDTH; i <= KERNEL_WIDTH; i++) {
		for (int j = -KERNEL_WIDTH; j <= KERNEL_WIDTH; j++) {
			vec4 sample = texture(tex, sp);
			if (sample.a > 0.5) { 
				pCol.rgb += sample.rgb;
				samples += 1.0;
			}
			sp.x += texel.x;
		}
		sp.x = spInit.x;
		sp.y += texel.y;
	}

	pCol.rgb /= samples;
	pCol.a = 1.0;
}