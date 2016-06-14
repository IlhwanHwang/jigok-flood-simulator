//
// AcornBusTwoRideEachTaste 2016.06.10
// Fluid simulation UI
//

#include "fluid_ui.h"
#include "shader.h"
#include "mat.h"
#include "config.h"
#include "debug.h"
#include "key.h"

#include <vector>

float FluidUI::viewAngleZ = 1.0, FluidUI::viewAngleY = 0.3;
int FluidUI::mouse_px = -1, FluidUI::mouse_py = -1;
bool FluidUI::pressed = false;

void FluidUI::mousefunction(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			pressed = true;
			mouse_px = x;
			mouse_py = y;
		}
		if (state == GLUT_UP) {
			pressed = false;
		}
	}
}

void FluidUI::motionfunction(int x, int y) {
	if (pressed)
	{
		viewAngleZ -= (float)(x - mouse_px) * 0.004;
		viewAngleY += (float)(y - mouse_py) * 0.002;
		viewAngleY = fminf(viewAngleY, 1.5);
		viewAngleY = fmaxf(viewAngleY, -1.5);
		mouse_px = x;
		mouse_py = y;
	}
}

void FluidUI::init(
	float physicalSpaceX,
	float physicalSpaceY,
	float physicalSpaceZ)
{
	fov = 20.0;

	//Texture
	//texCircle.load("image\\circle.png");

	std::vector<unsigned char> dataCircle;
	int w = 32;
	int h = 32;
	int cw = 16;
	int ch = 16;
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			float x, y, z, a;
			x = (float)(i - w / 2) / (cw / 2);
			y = (float)(j - h / 2) / (ch / 2);
			a = (x*x + y*y) > 1 ? 0.0 : 255.0;
			z = sqrt(1 - (x*x + y*y));
			x += 1.0;
			x *= 0.5 * 255;
			y += 1.0;
			y *= 0.5 * 255;
			z += 1.0;
			z *= 0.5 * 255;
			dataCircle.push_back((unsigned char)x);
			dataCircle.push_back((unsigned char)y);
			dataCircle.push_back((unsigned char)z);
			dataCircle.push_back((unsigned char)a);
		}
	}
	texCircle.push(w, h, &dataCircle[0]);
	dataCircle.clear();

	texBloom.load("image\\bloom.png");
	texColormap.load("image\\colormap.png");

#ifdef SCINARIO_JIGOK
	//Texture
	{
		texAroundPond.load("Image\\around_pond.png");
		texASP.load("Image\\asp.png");
		texASP2.load("Image\\asp2.png");
		texGrMiddle.load("Image\\gr_middle.png");
		texGrass1.load("Image\\grass1.png");
		texGrass2.load("Image\\grass2.png");
		texGrass12.load("Image\\grass12.png");
		texGrass13.load("Image\\grass13.png");
		texGrass15.load("Image\\grass15.png");
		texIndo.load("Image\\indo.png");
		texIndo2.load("Image\\indo2.png");
		texRoof.load("Image\\roof.png");
		texStair.load("Image\\stair.png");
		texStone.load("Image\\stone.png");
		texWall.load("Image\\wall.png");

		normAroundPond.load("Image\\around_pond_texture.png");
		normASP.load("Image\\asp_texture.png");
		normASP2.load("Image\\asp2_texture.png");
		normGrMiddle.load("Image\\gr_middle_texture.png");
		normGrass1.load("Image\\grass1_texture.png");
		normGrass2.load("Image\\grass2_texture.png");
		normGrass12.load("Image\\grass12_texture.png");
		normGrass13.load("Image\\grass13_texture.png");
		normGrass15.load("Image\\grass15_texture.png");
		normIndo.load("Image\\indo_texture.png");
		normIndo2.load("Image\\indo2_texture.png");
		normRoof.load("Image\\roof_texture.png");
		normStair.load("Image\\stair_texture.png");
		normStone.load("Image\\stone_texture.png");
		normWall.load("Image\\wall_texture.png");
	}

	//Model
	{
		modelAroundPond.load("Model\\around_pond.obj");
		modelASP.load("Model\\asp.obj");
		modelASP2.load("Model\\asp2.obj");
		modelGrMiddle.load("Model\\gr_middle.obj");
		modelGrass1.load("Model\\grass1.obj");
		modelGrass2.load("Model\\grass2.obj");
		modelGrass12.load("Model\\grass12.obj");
		modelGrass13.load("Model\\grass13.obj");
		modelGrass15.load("Model\\grass15.obj");
		modelIndo.load("Model\\indo.obj");
		modelIndo2.load("Model\\indo2.obj");
		modelRoof.load("Model\\roof.obj");
		modelStair.load("Model\\stair.obj");
		modelStone.load("Model\\stone.obj");
		modelWall.load("Model\\wall.obj");
	}
#endif

	//Renderer Normal
	shdRenderNormal = glCreateProgram();
	loadShader(shdRenderNormal, GL_VERTEX_SHADER, "fluid_render_v.glsl");
	loadShader(shdRenderNormal, GL_GEOMETRY_SHADER, "fluid_render_g.glsl");
#ifdef SIMPLE_RENDER
	loadShader(shdRenderNormal, GL_FRAGMENT_SHADER, "fluid_render_simple_f.glsl");
#else
	loadShader(shdRenderNormal, GL_FRAGMENT_SHADER, "fluid_render_normal_f.glsl");
#endif
	linkProgram(shdRenderNormal);

	glUseProgram(shdRenderNormal);
	glUniform1i(glGetUniformLocation(shdRenderNormal, "mapPosition"), 0);
	glUniform1i(glGetUniformLocation(shdRenderNormal, "mapETC"), 1);
	glUniform1i(glGetUniformLocation(shdRenderNormal, "mapProp"), 2);
	glUniform1i(glGetUniformLocation(shdRenderNormal, "mapNorm"), 3);
	glUniform1i(glGetUniformLocation(shdRenderNormal, "tex"), 4);
	glUniform1i(glGetUniformLocation(shdRenderNormal, "mapColor"), 5);
	uniRNmatModelView = glGetUniformLocation(shdRenderNormal, "matModelView");
	uniRNmatProjection = glGetUniformLocation(shdRenderNormal, "matProjection");

#ifndef SIMPLE_RENDER
	//Renderer Absorb
	shdRenderAbsorb = glCreateProgram();
	loadShader(shdRenderAbsorb, GL_VERTEX_SHADER, "fluid_render_v.glsl");
	loadShader(shdRenderAbsorb, GL_GEOMETRY_SHADER, "fluid_render_g.glsl");
	loadShader(shdRenderAbsorb, GL_FRAGMENT_SHADER, "fluid_render_absorb_f.glsl");
	linkProgram(shdRenderAbsorb);

	glUseProgram(shdRenderAbsorb);
	glUniform1i(glGetUniformLocation(shdRenderAbsorb, "mapPosition"), 0);
	glUniform1i(glGetUniformLocation(shdRenderAbsorb, "mapETC"), 1);
	glUniform1i(glGetUniformLocation(shdRenderAbsorb, "mapProp"), 2);
	glUniform1i(glGetUniformLocation(shdRenderAbsorb, "mapNorm"), 3);
	glUniform1i(glGetUniformLocation(shdRenderAbsorb, "tex"), 4);
	glUniform1i(glGetUniformLocation(shdRenderAbsorb, "mapColor"), 5);
	uniRAmatModelView = glGetUniformLocation(shdRenderAbsorb, "matModelView");
	uniRAmatProjection = glGetUniformLocation(shdRenderAbsorb, "matProjection");

	//Renderer Scatter
	shdRenderScatter = glCreateProgram();
	loadShader(shdRenderScatter, GL_VERTEX_SHADER, "fluid_render_v.glsl");
	loadShader(shdRenderScatter, GL_GEOMETRY_SHADER, "fluid_render_g.glsl");
	loadShader(shdRenderScatter, GL_FRAGMENT_SHADER, "fluid_render_scatter_f.glsl");
	linkProgram(shdRenderScatter);

	glUseProgram(shdRenderScatter);
	glUniform1i(glGetUniformLocation(shdRenderScatter, "mapPosition"), 0);
	glUniform1i(glGetUniformLocation(shdRenderScatter, "mapETC"), 1);
	glUniform1i(glGetUniformLocation(shdRenderScatter, "mapProp"), 2);
	glUniform1i(glGetUniformLocation(shdRenderScatter, "mapNorm"), 3);
	glUniform1i(glGetUniformLocation(shdRenderScatter, "tex"), 4);
	glUniform1i(glGetUniformLocation(shdRenderScatter, "mapColor"), 5);
	glUniform1i(glGetUniformLocation(shdRenderScatter, "mapVelocity"), 6);
	uniRSmatModelView = glGetUniformLocation(shdRenderScatter, "matModelView");
	uniRSmatProjection = glGetUniformLocation(shdRenderScatter, "matProjection");
#endif

	//Line cube render
	shdLinecube = glCreateProgram();
	loadShader(shdLinecube, GL_VERTEX_SHADER, "linecube_v.glsl");
	loadShader(shdLinecube, GL_FRAGMENT_SHADER, "linecube_f.glsl");
	linkProgram(shdLinecube);

	uniLCmatModelView = glGetUniformLocation(shdLinecube, "matModelView");
	uniLCmatProjection = glGetUniformLocation(shdLinecube, "matProjection");

	//Line cube VBO
	std::vector<float> data;

	glGenBuffers(1, &vboLinecube);
	glBindBuffer(GL_ARRAY_BUFFER, vboLinecube);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			if (!(i & (1 << j))) {
				int k = i ^ (1 << j);

				float x1 = i & 1 ? -1.0 : 1.0;
				float x2 = k & 1 ? -1.0 : 1.0;
				float y1 = i & 2 ? -1.0 : 1.0;
				float y2 = k & 2 ? -1.0 : 1.0;
				float z1 = i & 4 ? -1.0 : 1.0;
				float z2 = k & 4 ? -1.0 : 1.0;

				data.push_back(x1);
				data.push_back(y1);
				data.push_back(z1);
				data.push_back(x2);
				data.push_back(y2);
				data.push_back(z2);
			}
		}
	}
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
	vboLinecubeSize = data.size() / 3;
	data.clear();

	this->physicalSpaceX = physicalSpaceX;
	this->physicalSpaceY = physicalSpaceY;
	this->physicalSpaceZ = physicalSpaceZ;
	viewDist = fmaxf(fmaxf(physicalSpaceX, physicalSpaceY), physicalSpaceZ) * 0.8;

	//Mouse functions
	glutMouseFunc(mousefunction);
	glutMotionFunc(motionfunction);
	
	//Phong
	shdPhong = glCreateProgram();
	loadShader(shdPhong, GL_VERTEX_SHADER, "phong_v.glsl");
	loadShader(shdPhong, GL_GEOMETRY_SHADER, "phong_g.glsl");
	loadShader(shdPhong, GL_FRAGMENT_SHADER, "phong_f.glsl");
	linkProgram(shdPhong);
	glUseProgram(shdPhong);
	glUniform1i(glGetUniformLocation(shdPhong, "tex"), 0);
	glUniform1i(glGetUniformLocation(shdPhong, "norm"), 1);
	uniPHmatModelView = glGetUniformLocation(shdPhong, "matModelView");
	uniPHmatProjection = glGetUniformLocation(shdPhong, "matProjection");
	uniPHlight = glGetUniformLocation(shdPhong, "light");
	uniPHlightEye = glGetUniformLocation(shdPhong, "lightEye");

	//Env test render
	shdEnvTest = glCreateProgram();
	loadShader(shdEnvTest, GL_VERTEX_SHADER, "env_test_v.glsl");
	loadShader(shdEnvTest, GL_FRAGMENT_SHADER, "env_test_f.glsl");
	linkProgram(shdEnvTest);

	glUseProgram(shdEnvTest);
	glUniform1i(glGetUniformLocation(shdEnvTest, "env"), 0);
	uniETmatModelView = glGetUniformLocation(shdEnvTest, "matModelView");
	uniETmatProjection = glGetUniformLocation(shdEnvTest, "matProjection");

	glGenBuffers(1, &vboEnvTest);
	glBindBuffer(GL_ARRAY_BUFFER, vboEnvTest);
	for (int i = 0; i < 128; i++) {
		float z = i / 64.0 - 1.0;
		float w = i / 128.0;
		data.push_back(-1.0);
		data.push_back(-1.0);
		data.push_back(z);
		data.push_back(0.0);
		data.push_back(0.0);
		data.push_back(w);

		data.push_back(1.0);
		data.push_back(-1.0);
		data.push_back(z);
		data.push_back(1.0);
		data.push_back(0.0);
		data.push_back(w);

		data.push_back(-1.0);
		data.push_back(1.0);
		data.push_back(z);
		data.push_back(0.0);
		data.push_back(1.0);
		data.push_back(w);

		data.push_back(1.0);
		data.push_back(-1.0);
		data.push_back(z);
		data.push_back(1.0);
		data.push_back(0.0);
		data.push_back(w);

		data.push_back(-1.0);
		data.push_back(1.0);
		data.push_back(z);
		data.push_back(0.0);
		data.push_back(1.0);
		data.push_back(w);

		data.push_back(1.0);
		data.push_back(1.0);
		data.push_back(z);
		data.push_back(1.0);
		data.push_back(1.0);
		data.push_back(w);
	}
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
	vboEnvTestSize = data.size() / 6;
	data.clear();

#ifndef SIMPLE_RENDER
	//Render buffers
	glGenTextures(1, &texNormal);
	glBindTexture(GL_TEXTURE_2D, texNormal);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	glGenTextures(1, &texAbsorb);
	glBindTexture(GL_TEXTURE_2D, texAbsorb);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	glGenTextures(1, &texScatter);
	glBindTexture(GL_TEXTURE_2D, texScatter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	glGenTextures(1, &texDepth);
	glBindTexture(GL_TEXTURE_2D, texDepth);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RG32F, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RG, GL_FLOAT, NULL);

	glGenTextures(1, &depRendertemp);
	glBindTexture(GL_TEXTURE_2D, depRendertemp);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, SCREEN_WIDTH, SCREEN_HEIGHT, 0,
		GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);

	glGenFramebuffers(1, &fbRendertemp);
	glBindFramebuffer(GL_FRAMEBUFFER, fbRendertemp);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texNormal, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depRendertemp, 0);

	shdSprite = glCreateProgram();
	loadShader(shdSprite, GL_VERTEX_SHADER, "sprite_v.glsl");
	loadShader(shdSprite, GL_GEOMETRY_SHADER, "sprite_g.glsl");
	loadShader(shdSprite, GL_FRAGMENT_SHADER, "sprite_f.glsl");
	linkProgram(shdSprite);

	glUseProgram(shdSprite);
	glUniform1i(glGetUniformLocation(shdSprite, "tex"), 0);
	uniSPmatModelView = glGetUniformLocation(shdSprite, "matModelView");
	uniSPmatProjection = glGetUniformLocation(shdSprite, "matProjection");
	uniSPwidth = glGetUniformLocation(shdSprite, "width");
	uniSPheight = glGetUniformLocation(shdSprite, "height");
	uniSPbias = glGetUniformLocation(shdSprite, "bias");
	uniSPscale = glGetUniformLocation(shdSprite, "scale");

	glGenBuffers(1, &vboZeropoint);
	glBindBuffer(GL_ARRAY_BUFFER, vboZeropoint);
	data.push_back(0.0);
	data.push_back(0.0);
	data.push_back(0.0);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
	data.clear();

	shdFastblur = glCreateProgram();
	loadShader(shdFastblur, GL_VERTEX_SHADER, "framepass_v.glsl");
	loadShader(shdFastblur, GL_GEOMETRY_SHADER, "framepass_g.glsl");
	loadShader(shdFastblur, GL_FRAGMENT_SHADER, "fastblur_f.glsl");
	linkProgram(shdFastblur);
	glUniform1i(glGetUniformLocation(shdFastblur, "tex"), 0);
	glUniform2f(glGetUniformLocation(shdFastblur, "texel"), 1.0 / SCREEN_WIDTH, 1.0 / SCREEN_HEIGHT);

	shdFluidPhong = glCreateProgram();
	loadShader(shdFluidPhong, GL_VERTEX_SHADER, "framepass_v.glsl");
	loadShader(shdFluidPhong, GL_GEOMETRY_SHADER, "framepass_g.glsl");
	loadShader(shdFluidPhong, GL_FRAGMENT_SHADER, "fluid_phong_f.glsl");
	linkProgram(shdFluidPhong);
	glUniform1i(glGetUniformLocation(shdFluidPhong, "normal"), 0);
	uniFPlight = glGetUniformLocation(shdFluidPhong, "light");

	glGenTextures(1, &texPhong);
	glBindTexture(GL_TEXTURE_2D, texPhong);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	shdDepthStencil = glCreateProgram();
	loadShader(shdDepthStencil, GL_VERTEX_SHADER, "framepass_v.glsl");
	loadShader(shdDepthStencil, GL_GEOMETRY_SHADER, "framepass_g.glsl");
	loadShader(shdDepthStencil, GL_FRAGMENT_SHADER, "depth_stencil_f.glsl");
	linkProgram(shdDepthStencil);
	glUniform1i(glGetUniformLocation(shdDepthStencil, "tex"), 0);
	glUniform1i(glGetUniformLocation(shdDepthStencil, "dep"), 1);
	uniDSdepOffset = glGetUniformLocation(shdDepthStencil, "depOffset");

	glGenTextures(1, &texBlurredNormal);
	glBindTexture(GL_TEXTURE_2D, texBlurredNormal);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
#endif
}

void FluidUI::update() {
	const float rate = 0.95;
	if (Key::keyCheckOn('w')) {
		viewDist *= rate;
	}
	if (Key::keyCheckOn('s')) {
		viewDist /= rate;
	}
}

void FluidUI::draw(
	GLuint vboParticleForEach,
	unsigned int particleMax,
	GLuint mapPosition,
	GLuint mapVelocity,
	GLuint mapETC,
	GLuint mapProp,
	GLuint mapNorm,
	Model& modelEnv,
	mat4& matEnvModelview,
	GLuint mapWallField)
{
	vec3 light = normalize(vec3(0.5, 0.5, 1.0));
	float scale = 100.0;

	mat4 modelview, projection;
	vec4 eye, at, up;

	eye = vec4(vec3(
		cosf(viewAngleZ) * cosf(viewAngleY),
		sinf(viewAngleZ) * cosf(viewAngleY),
		sinf(viewAngleY)) * viewDist * 12.0 * scale, 1.0);
	at = vec4(0.0, 0.0, 0.0, 1.0);
	up = vec4(0.0, 0.0, 1.0, 0.0);

	modelview *= Matrix::Scale(2.0, 2.0, 2.0);
	modelview *= Matrix::Scale(scale, scale, scale);
	modelview *= Matrix::Translate(-vec4(physicalSpaceX, physicalSpaceY, physicalSpaceZ, 0.0) * 0.5);

	projection *= Matrix::Perspective(fov, 1.0, 1.0, viewDist * 30.0 * scale);
	projection *= Matrix::LookAt(eye, at, up);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#ifdef SIMPLE_RENDER
	//Particle simple render
	{
		glUseProgram(shdRenderNormal);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mapPosition);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, mapETC);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, mapProp);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, mapNorm);
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, texCircle.tex());
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, texColormap.tex());

		glUniformMatrix4fv(uniRNmatModelView, 1, GL_TRUE, modelview);
		glUniformMatrix4fv(uniRNmatProjection, 1, GL_TRUE, projection);

		glBindBuffer(GL_ARRAY_BUFFER, vboParticleForEach);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glDrawArrays(GL_POINTS, 0, particleMax);
		glDisableVertexAttribArray(0);
	}
#endif

#ifndef SIMPLE_RENDER
	//Particle normal render
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbRendertemp);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texNormal, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, texDepth, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depRendertemp, 0);
		GLenum buf[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
		glDrawBuffers(2, buf);

		glClearDepth(1.0);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shdRenderNormal);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mapPosition);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, mapETC);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, mapProp);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, mapNorm);
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, texCircle.tex());
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, texColormap.tex());

		glUniformMatrix4fv(uniRNmatModelView, 1, GL_TRUE, modelview);
		glUniformMatrix4fv(uniRNmatProjection, 1, GL_TRUE, projection);

		glBindBuffer(GL_ARRAY_BUFFER, vboParticleForEach);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glDrawArrays(GL_POINTS, 0, particleMax);
		glDisableVertexAttribArray(0);
	}

	//Particle absorbtion render
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbRendertemp);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texAbsorb, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depRendertemp, 0);
		GLenum buf = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, &buf);

		glClearDepth(1.0);
		glClearColor(1.0, 1.0, 1.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendEquationSeparate(GL_FUNC_REVERSE_SUBTRACT, GL_FUNC_ADD);
		glBlendFuncSeparate(GL_ONE, GL_ONE, GL_ONE_MINUS_DST_ALPHA, GL_ONE);

		glUseProgram(shdRenderAbsorb);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mapPosition);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, mapETC);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, mapProp);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, mapNorm);
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, texBloom.tex());
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, texColormap.tex());

		glUniformMatrix4fv(uniRAmatModelView, 1, GL_TRUE, modelview);
		glUniformMatrix4fv(uniRAmatProjection, 1, GL_TRUE, projection);

		glBindBuffer(GL_ARRAY_BUFFER, vboParticleForEach);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glDrawArrays(GL_POINTS, 0, particleMax);
		glDisableVertexAttribArray(0);

		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
	}

	//Particle scatter render
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbRendertemp);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texScatter, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depRendertemp, 0);
		GLenum buf = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, &buf);

		glClearDepth(1.0);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
		glBlendFuncSeparate(GL_ONE_MINUS_DST_COLOR, GL_ONE, GL_ONE_MINUS_DST_ALPHA, GL_ONE);

		glUseProgram(shdRenderScatter);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mapPosition);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, mapETC);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, mapProp);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, mapNorm);
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, texBloom.tex());
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, texColormap.tex());
		glActiveTexture(GL_TEXTURE6);
		glBindTexture(GL_TEXTURE_2D, mapVelocity);

		glUniformMatrix4fv(uniRSmatModelView, 1, GL_TRUE, modelview);
		glUniformMatrix4fv(uniRSmatProjection, 1, GL_TRUE, projection);

		glBindBuffer(GL_ARRAY_BUFFER, vboParticleForEach);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glDrawArrays(GL_POINTS, 0, particleMax);
		glDisableVertexAttribArray(0);

		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
	}

	//Normal blurring
	{
		for (int i = 0; i < 4; i++) {
			glBindFramebuffer(GL_FRAMEBUFFER, fbRendertemp);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texBlurredNormal, 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depRendertemp, 0);
			GLenum buf = { GL_COLOR_ATTACHMENT0 };
			glDrawBuffers(1, &buf);

			glClearDepth(1.0);
			glClearColor(0.0, 0.0, 0.0, 0.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glUseProgram(shdFastblur);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texNormal);

			glBindBuffer(GL_ARRAY_BUFFER, vboZeropoint);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
			glDrawArrays(GL_POINTS, 0, 1);
			glDisableVertexAttribArray(0);

			GLuint temp = texBlurredNormal;
			texBlurredNormal = texNormal;
			texNormal = temp;
		}
	}

	//Phong
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbRendertemp);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texPhong, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depRendertemp, 0);
		GLenum buf = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, &buf);

		glClearDepth(1.0);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shdFluidPhong);

		vec4 fplight = projection * vec4(light, 0.0);
		glUniform3fv(uniFPlight, 1, normalize(vec3(fplight.x, fplight.y, fplight.z)));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texBlurredNormal);

		glBindBuffer(GL_ARRAY_BUFFER, vboZeropoint);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glDrawArrays(GL_POINTS, 0, 1);
		glDisableVertexAttribArray(0);
	}
#endif

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//Linecube render
	{
		glUseProgram(shdLinecube);

		modelview = Matrix::Scale(scale, scale, scale);
		modelview *= Matrix::Scale(physicalSpaceX, physicalSpaceY, physicalSpaceZ);
		glUniformMatrix4fv(uniLCmatModelView, 1, GL_TRUE, modelview);
		glUniformMatrix4fv(uniLCmatProjection, 1, GL_TRUE, projection);

		glBindBuffer(GL_ARRAY_BUFFER, vboLinecube);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glDrawArrays(GL_LINES, 0, vboLinecubeSize);
		glDisableVertexAttribArray(0);
	}

#ifdef SCINARIO_JIGOK
	//Environment
	{
		glUseProgram(shdPhong);

		mat4 modelview2 = Matrix::Scale(scale, scale, scale) * matEnvModelview;
		modelview2 = Matrix::Translate(0.0, 0.0, -5.0) * modelview2;

		glUniformMatrix4fv(uniPHmatModelView, 1, GL_TRUE, modelview2);
		glUniformMatrix4fv(uniPHmatProjection, 1, GL_TRUE, projection);
		glUniform3fv(uniPHlight, 1, light);
		glUniform3fv(uniPHlightEye, 1, vec3(eye.x, eye.y, eye.z));

		drawModels(modelAroundPond, texAroundPond, normAroundPond);
		drawModels(modelASP, texASP, normASP);
		drawModels(modelASP2, texASP2, normASP2);
		drawModels(modelGrMiddle, texGrMiddle, normGrMiddle);
		drawModels(modelGrass1, texGrass1, normGrass1);
		drawModels(modelGrass2, texGrass2, normGrass2);
		drawModels(modelGrass12, texGrass12, normGrass12);
		drawModels(modelGrass13, texGrass13, normGrass13);
		drawModels(modelGrass15, texGrass15, normGrass15);
		drawModels(modelIndo, texIndo, normIndo);
		drawModels(modelIndo2, texIndo2, normIndo2);
		drawModels(modelRoof, texRoof, normRoof);
		drawModels(modelStair, texStair, normStair);
		drawModels(modelStone, texStone, normStone);
		drawModels(modelWall, texWall, normWall);
	}
#endif
	//Environment Test
	{
		/*
		modelview = Matrix::Scale(scale, scale, scale);
		modelview *= Matrix::Scale(physicalSpaceX, physicalSpaceY, physicalSpaceZ);
		glUseProgram(shdEnvTest);
		glUniformMatrix4fv(uniETmatModelView, 1, GL_TRUE, modelview);
		glUniformMatrix4fv(uniETmatProjection, 1, GL_TRUE, projection);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_3D, mapWallField);

		glBindBuffer(GL_ARRAY_BUFFER, vboEnvTest);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));
		glDrawArrays(GL_TRIANGLES, 0, vboEnvTestSize);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		*/
	}

#ifndef SIMPLE_RENDER
	//Fluid Composition
	{
		glUseProgram(shdDepthStencil);

		glEnable(GL_BLEND);

		//Absorbtion
		{
			glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
			glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_ONE);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texAbsorb);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texDepth);
			glUniform1f(uniDSdepOffset, 0.0);

			glBindBuffer(GL_ARRAY_BUFFER, vboZeropoint);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
			glDrawArrays(GL_POINTS, 0, 1);
			glDisableVertexAttribArray(0);
		}

		//Specular
		{
			glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
			glBlendFuncSeparate(GL_ONE, GL_ONE, GL_ONE, GL_ONE);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texPhong);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texDepth);
			glUniform1f(uniDSdepOffset, 0.0);

			glBindBuffer(GL_ARRAY_BUFFER, vboZeropoint);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
			glDrawArrays(GL_POINTS, 0, 1);
			glDisableVertexAttribArray(0);
		}
		
		//Scatter
		{
			glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
			glBlendFuncSeparate(GL_ONE_MINUS_DST_COLOR, GL_ONE, GL_ONE_MINUS_DST_ALPHA, GL_ONE);
			//glBlendFuncSeparate(GL_ONE, GL_ONE, GL_ONE_MINUS_DST_ALPHA, GL_ONE);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texScatter);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texDepth);
			glUniform1f(uniDSdepOffset, 0.0);

			glBindBuffer(GL_ARRAY_BUFFER, vboZeropoint);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
			glDrawArrays(GL_POINTS, 0, 1);
			glDisableVertexAttribArray(0);
		}
		
		glDisable(GL_BLEND);
	}
#endif
}

void FluidUI::drawModels(Model& mod, Texture& tex, Texture& norm) {
	glUseProgram(shdPhong);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex.tex());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, norm.tex());

	mod.draw();
}