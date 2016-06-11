uniform float neighborCellSizeX;
uniform float neighborCellSizeY;
uniform float neighborCellSizeZ;
uniform float neighborCellNumX;
uniform float neighborCellNumY;
uniform float neighborCellNumZ;
uniform float neighborCellLength;

vec3 pos2grid(vec3 pos) {
	return vec3(
		floor(pos.x / neighborCellSizeX),
		floor(pos.y / neighborCellSizeY),
		floor(pos.z / neighborCellSizeZ)
	);
}

vec2 grid2nid(vec3 grid, float stagef) {
	return vec2(
		((grid.x + 0.5) / neighborCellNumX + grid.z) / neighborCellNumZ,
		((grid.y + 0.5) / neighborCellNumY + stagef) / neighborCellLength
	);
}