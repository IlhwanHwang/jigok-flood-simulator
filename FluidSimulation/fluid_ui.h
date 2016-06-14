//
// AcornBusTwoRideEachTaste 2016.06.10
// Fluid simulation UI
//

#pragma once

#include <GL/glew.h>

#include <GL/freeglut.h>
#include "texture.h"
#include "model.h"
#include "mat.h"

class FluidUI {
private:
	static float viewAngleZ;
	static float viewAngleY;
	static int mouse_px, mouse_py;
	static bool pressed;
	Texture texCircle;
	Texture texBloom;
	Texture texColormap;

	float fov;

	GLuint shdRenderNormal;
	GLuint uniRNmatModelView;
	GLuint uniRNmatProjection;

	GLuint shdRenderAbsorb;
	GLuint uniRAmatModelView;
	GLuint uniRAmatProjection;

	GLuint shdRenderScatter;
	GLuint uniRSmatModelView;
	GLuint uniRSmatProjection;

	GLuint shdLinecube;
	GLuint uniLCmatModelView;
	GLuint uniLCmatProjection;
	GLuint vboLinecube;
	unsigned int vboLinecubeSize;

	GLuint shdPhong;
	GLuint uniPHmatModelView;
	GLuint uniPHmatProjection;
	GLuint uniPHlight;
	GLuint uniPHlightEye;

	GLuint shdEnvTest;
	GLuint uniETmatModelView;
	GLuint uniETmatProjection;
	GLuint vboEnvTest;
	unsigned int vboEnvTestSize;

	GLuint texNormal;
	GLuint texAbsorb;
	GLuint texScatter;
	GLuint depRendertemp;
	GLuint texDepth;
	GLuint fbRendertemp;

	GLuint shdFastblur;
	GLuint texBlurredNormal;

	GLuint shdFluidPhong;
	GLuint uniFPlight;
	GLuint texPhong;

	GLuint shdDepthStencil;
	GLuint uniDSdepOffset;

	GLuint shdSprite;
	GLuint uniSPmatModelView;
	GLuint uniSPmatProjection;
	GLuint uniSPwidth;
	GLuint uniSPheight;
	GLuint uniSPbias;
	GLuint uniSPscale;
	GLuint vboZeropoint;

	Texture texAroundPond;
	Texture texASP;
	Texture texASP2;
	Texture texGrMiddle;
	Texture texGrass1;
	Texture texGrass2;
	Texture texGrass12;
	Texture texGrass13;
	Texture texGrass15;
	Texture texIndo;
	Texture texIndo2;
	Texture texRoof;
	Texture texStair;
	Texture texStone;
	Texture texWall;

	Texture normAroundPond;
	Texture normASP;
	Texture normASP2;
	Texture normGrMiddle;
	Texture normGrass1;
	Texture normGrass2;
	Texture normGrass12;
	Texture normGrass13;
	Texture normGrass15;
	Texture normIndo;
	Texture normIndo2;
	Texture normRoof;
	Texture normStair;
	Texture normStone;
	Texture normWall;

	Model modelAroundPond;
	Model modelASP;
	Model modelASP2;
	Model modelGrMiddle;
	Model modelGrass1;
	Model modelGrass2;
	Model modelGrass12;
	Model modelGrass13;
	Model modelGrass15;
	Model modelIndo;
	Model modelIndo2;
	Model modelRoof;
	Model modelStair;
	Model modelStone;
	Model modelWall;

	float physicalSpaceX, physicalSpaceY, physicalSpaceZ;
	float viewDist;

	void drawModels(Model& mod, Texture& tex, Texture& norm);

public:
	static void mousefunction(int button, int state, int x, int y);
	static void motionfunction(int x, int y);
	void init(
		float physicalSpaceX, 
		float physicalSpaceY, 
		float physicalSpaceZ);
	void update();
	void draw(
		GLuint vboParticleForEach,
		unsigned int particleMax,
		GLuint mapPosition,
		GLuint mapVelocity,
		GLuint mapETC,
		GLuint mapProp,
		GLuint mapNorm,
		Model& modelEnv,
		mat4& matEnvModelview,
		GLuint mapWallField);
};