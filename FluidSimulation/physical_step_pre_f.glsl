#version 330

in vec2 fpid;

#include "map.glsl"

layout (location = 0) out vec2 prop;

#include "neighbor_grid.glsl"
#include "kernel.glsl"
#include "physical.glsl"

void main() {
	vec3 pos = texture2D(mapPosition, fpid).xyz;

	float density = 0.0;

	vec3 grid = pos2grid(pos);
	vec3 dgrid = vec3(-1.0, -1.0, -1.0);

	for (int i = -1; i <= 1; i++) {
		if (grid.z + dgrid.z < -0.5) {
			dgrid.y = -1.0;
			dgrid.z += 1.0;
			continue;
		}
		if (grid.z + dgrid.z > neighborCellNumZ - 0.5)
			break;

		for (int j = -1; j <= 1; j++) {
			if (grid.y + dgrid.y < -0.5) {
				dgrid.x = -1.0;
				dgrid.y += 1.0;
				continue;
			}
			if (grid.y + dgrid.y > neighborCellNumY - 0.5)
				break;

			for (int k = -1; k <= 1; k++) {
				if (grid.x + dgrid.x < -0.5) {
					dgrid.x += 1.0;
					continue;
				}
				if (grid.x + dgrid.x > neighborCellNumX - 0.5)
					break;

				float stagef = 0.0;
				for (int n = 0; n < neighborCellLength; n++) {
					vec2 nid = grid2nid(grid + dgrid, stagef);
					vec3 neighbor = texture2D(mapNeighbor, nid).rgb;

					if (neighbor.b < 0.5)
						break;

					vec2 opid = neighbor.xy;
					vec3 opos = texture2D(mapPosition, opid).rgb;

					if (length(pos - opos) < h)
						density += wpoly6(length(pos - opos));
					
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

	density *= particleMass;

	float pressure = physicalStiffness * (density - physicalRestDensity);

	prop.r = density;
	prop.g = pressure;
}