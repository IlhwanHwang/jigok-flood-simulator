#version 330

in vec2 fpid;

#include "map.glsl"

layout (location = 0) out vec3 npos;
layout (location = 1) out vec3 nvel;
layout (location = 2) out vec3 norm;

#include "neighbor_grid.glsl"
#include "kernel.glsl"
#include "physical.glsl"

void main() {
	vec3 pos = texture2D(mapPosition, fpid).xyz;
	vec3 vel = texture2D(mapVelocity, fpid).xyz;
	vec2 prop = texture2D(mapProp, fpid).xy;
	float density = prop.r;
	float pressure = prop.g;

	vec3 forcePressure;
	vec3 forceViscosity;
	vec3 forceSurface;
	vec3 forceGravity = gravity * density;
	vec3 colorFieldNormal;
	float colorFieldLapl = 0.0;

	vec3 grid = pos2grid(pos);
	vec3 dgrid = vec3(-1.0, -1.0, -1.0);

	//Do not discard out-of-grid case.
	//It is guaranteed that all particles are in grid range 1 ~ n-2
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			for (int k = -1; k <= 1; k++) {
				float stagef = 0.0;
				for (int n = 0; n < neighborCellLength; n++) {
					vec2 nid = grid2nid(grid + dgrid, stagef);
					vec3 neighbor = texture2D(mapNeighbor, nid).rgb;

					if (neighbor.b < 0.5)
						break;

					vec2 opid = neighbor.xy;
					vec3 opos = texture2D(mapPosition, opid).rgb;
					vec3 ovel = texture2D(mapVelocity, opid).rgb;
					vec2 oprop = texture2D(mapProp, opid).rg;
					float odensity = oprop.r;
					float opressure = oprop.g;

					vec3 dpos = pos - opos;

					if (length(dpos) < h) {
						if (dot(dpos, dpos) > 0.0) { //No self interaction
							forcePressure += (
								pressure / pow(density, 2.0) +
								opressure / pow(odensity, 2.0) * wspikygrad(dpos)
							);
							forceViscosity += (
								(ovel - vel) * wviscositylapl(length(dpos)) / odensity
							);
						}
						colorFieldNormal += wpoly6grad(dpos) / odensity;
						colorFieldLapl += wpoly6lapl(length(dpos)) / odensity;
					}

					stagef += 1.0;
				}
				dgrid.x += 1.0;
			}
			dgrid.x = -1.0;
			dgrid.y += 1.0;
		}
		dgrid.y = -1.0;
		dgrid.z += 1.0;
	}

	forcePressure *= -particleMass * density;
	forceViscosity *= physicalViscosity * particleMass;
	colorFieldNormal *= particleMass;
	colorFieldLapl *= particleMass;

	if (length(colorFieldNormal) > physicalSurfaceTensionThres) {
		forceSurface = -physicalSurfaceTension * normalize(colorFieldNormal) * colorFieldLapl;
	}

	const vec3 wallset[6] =
	vec3[](
		vec3(0.0, 0.0, 0.0),
		vec3(0.0, 0.0, 0.0),
		vec3(0.0, 0.0, 0.0),
		vec3(1.0, 0.0, 0.0),
		vec3(0.0, 1.0, 0.0),
		vec3(0.0, 0.0, 1.0)
	);
	const vec3 wallnorm[6] = 
	vec3[](
		vec3(1.0, 0.0, 0.0),
		vec3(0.0, 1.0, 0.0),
		vec3(0.0, 0.0, 1.0),
		vec3(-1.0, 0.0, 0.0),
		vec3(0.0, -1.0, 0.0),
		vec3(0.0, 0.0, -1.0)
	);
	const int wallnum = 6;

	vec3 forceWall;

	vec3 world = vec3(physicalSpaceX, physicalSpaceY, physicalSpaceZ);
	for (int i = 0; i < wallnum; i++) {
		vec3 wallpos = wallset[i] * world + 2.0 * h * wallnorm[i];
		float dx = max(0.0, dot(wallpos - pos, wallnorm[i]));
		forceWall += dx * wallnorm[i] * physicalWallK;
		forceWall -= physicalWallDamp * dot(vel, wallnorm[i]) * wallnorm[i] * density * sign(dx);
	}

	vec3 wsamPos = pos / vec3(physicalSpaceX, physicalSpaceY, physicalSpaceZ);
	vec3 wsamNorm = texture(mapWallField, wsamPos).rgb;

	forceWall += wsamNorm * physicalWallK * length(wallfieldTexel);
	forceWall -= physicalWallDamp * dot(vel, wsamNorm) * wsamNorm * density;

	vec3 acc = (
		forcePressure + 
		forceViscosity + 
		forceSurface + 
		forceGravity +
		forceWall
	) / density;

	nvel = vel + acc * physicalDeltaTime;
	npos = pos + nvel * physicalDeltaTime;
	norm = normalize(colorFieldNormal);
}