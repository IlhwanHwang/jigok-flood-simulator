const float particleMass = 0.0025;
const float physicalStiffness = 3.0;
const float physicalRestDensity = 998.29;
const float physicalViscosity = 3.5;
const float physicalSurfaceTensionThres = 7.065;
const float physicalSurfaceTension = 0.0728;
const float physicalWallDamp = 100.0;
const float physicalWallK = 100000000.0;

uniform float physicalDeltaTime;
uniform float physicalSpaceX;
uniform float physicalSpaceY;
uniform float physicalSpaceZ;

const vec3 gravity = vec3(0.0, 0.0, -9.81);