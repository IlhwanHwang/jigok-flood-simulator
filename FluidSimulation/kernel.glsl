const float h = 0.011425;
const float h2 = h * h;
const float h3inv = 1.0 / h2 / h;
const float h6inv = h3inv * h3inv;
const float h9inv = h6inv * h3inv;
const float lowerBound = h / 1000.0;

const float pi = 3.1415926535;

float wpoly6(float r) {
	return (315.0 / 64.0 / pi * h9inv) * pow(max(lowerBound, h2 - r * r), 3.0);
}

vec3 wpoly6grad(vec3 r) {
	return (-945.0 / 32.0 / pi * h9inv) * pow(max(lowerBound, h2 - dot(r, r)), 2.0) * r;
}

float wpoly6lapl(float r) {
	return (-945.0 / 32.0 / pi * h9inv) *  
		(3.0 * pow(max(lowerBound, h2 - r * r), 2.0) - 4.0 * r * r * (h2 - r * r));
}

float wspiky(float r) {
	return (15.0 / pi * h6inv) * pow(max(lowerBound, h - r), 3.0);
}

vec3 wspikygrad(vec3 r) {
	return (-45.0 / pi * h6inv) * pow(max(lowerBound, h - length(r)), 2.0) * r / max(lowerBound, length(r));
}

float wspikylapl(float r) {
	return (-90.0 / pi * h6inv) * (pow(max(lowerBound, h - r), 2.0) - (h - r)) / r;
}

float wviscositylapl(float r) {
	return (45.0 / pi * h6inv) * (h - r);
}