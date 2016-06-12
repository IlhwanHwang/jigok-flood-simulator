//
// AcornBusTwoRideEachTaste 2016.06.10
// Fluid simulation UI
//

#include "fluid_ui.h"
#include "shader.h"
#include "mat.h"

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
	//Texture
	texCircle.load("image\\circle.png");
	texColormap.load("image\\colormap.png");

	//Renderer
	shdRender = glCreateProgram();
	loadShader(shdRender, GL_VERTEX_SHADER, "fluid_render_v.glsl");
	loadShader(shdRender, GL_GEOMETRY_SHADER, "fluid_render_g.glsl");
	loadShader(shdRender, GL_FRAGMENT_SHADER, "fluid_render_f.glsl");
	linkProgram(shdRender);

	glUseProgram(shdRender);
	glUniform1i(glGetUniformLocation(shdRender, "mapPosition"), 0);
	glUniform1i(glGetUniformLocation(shdRender, "mapETC"), 1);
	glUniform1i(glGetUniformLocation(shdRender, "mapProp"), 2);
	glUniform1i(glGetUniformLocation(shdRender, "tex"), 3);
	glUniform1i(glGetUniformLocation(shdRender, "mapColor"), 4);
	uniRDmatModelView = glGetUniformLocation(shdRender, "matModelView");
	uniRDmatProjection = glGetUniformLocation(shdRender, "matProjection");

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
	viewDist = fmaxf(fmaxf(physicalSpaceX, physicalSpaceY), physicalSpaceZ) * 0.7;

	glutMouseFunc(mousefunction);
	glutMotionFunc(motionfunction);
}

void FluidUI::draw(
	GLuint vboParticleForEach, 
	unsigned int particleMax,
	GLuint mapPosition,
	GLuint mapETC,
	GLuint mapProp)
{
	//Particle render
	glUseProgram(shdRender);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mapPosition);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, mapETC);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, mapProp);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texCircle.tex());
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, texColormap.tex());

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

	projection *= Matrix::Perspective(20.0, 1.0, 1.0, viewDist * 30.0 * scale);
	projection *= Matrix::LookAt(eye, at, up);

	glUniformMatrix4fv(uniRDmatModelView, 1, GL_TRUE, modelview);
	glUniformMatrix4fv(uniRDmatProjection, 1, GL_TRUE, projection);

	glBindBuffer(GL_ARRAY_BUFFER, vboParticleForEach);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawArrays(GL_POINTS, 0, particleMax);
	glDisableVertexAttribArray(0);

	//Linecube render
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