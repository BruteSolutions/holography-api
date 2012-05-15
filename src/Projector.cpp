#include <vector>

#include <glload/gl_3_3.h>
#include <GL/freeglut.h>

#include "Shared.h"
#include "Shader.h"
#include "GraphicalObject.h"
#include "ThreeDSpace.h"
#include "Scene.h"
#include "ColorTranslator.h"
#include "Projector.h"

/*
 * Creates a new projector with buffer of size len at the place pointer with position pos
 * and direction dir;
 */
Projector::Projector(int * pointer, unsigned int len, Vec3 pos, Vec3 dir) : highlighted(false) {
	colorTranslator = new ColorTranslator(); //Creates a ColorTranslator with default values.
	pnt = pointer;
	bufferSize = len;
	setPosition(pos);
	setDirection(dir);

  memset(keystone.m, 0, sizeof(keystone.m));
  for(int i = 0; i < 16; i += 5) {
    keystone.m[i] = 1.0;
  }

/*
    1.0000         0         0    0.1429
    0.1429    0.8571         0    0.1429
         0         0    0.8571         0
    0.1429         0         0    1.0000
  keystone.m[3] = 0.1429;
  keystone.m[4] = 0.1429;
  keystone.m[5] = 0.8571;
  keystone.m[7] = 0.1429;
  keystone.m[10] = 0.8571;
  keystone.m[12] = 0.1429;
*/
}

/*
 * Creates a new projector with buffer of size len at the place pointer with position (0,0,0)
 * and direction (0,0,0);
 */
Projector::Projector(int * pointer, unsigned int len) { 
	//Projector(pointer, len, new Vec3(0, 0, 0), new Vec3 (0, 0, 0));
	Vec3 pos = {0,0,0}, dir = {0,0,0};
	Projector(pointer, len, pos, dir);
	//DID NOT WORK, CAUSED SEGMENTATION FAULT
}
/*
 * Sets the position of the projector to the value of the parametre.
 * @param The new position of the projector.
 */
void Projector::setPosition(Vec3 position) {
	pos = position;
}

/*
 * Returns the position of the projector as a Vec3 object.
 * @return the position of the projector
 */
Vec3 Projector::getPosition() {
	return pos;
}

/*
 * Sets the direction of the projectior to the parametre.
 * @param The new direction of the projector
 */
void Projector::setDirection(Vec3 _direction) {
	direction = _direction;
}

/*
 * Returns the direction of the projector as a Vec3 object.
 * @return the direction of the projector
 */
Vec3 Projector::getDirection() {
	return direction;
}

/*
 * Returns the size of the buffer.
 * @return Size of the buffer.
 */
unsigned int Projector::getBufferSize() {
	return(bufferSize);
}

/*
  Returns the associated colortranslator object.
 * @return Colortranslator object.
 */
ColorTranslator * Projector::getColorTranslator() {
	return(colorTranslator);
}

/*
 * Set the current configuration.
 * @param c Configuration to be used.
 */
void Projector::setConfiguration(Configuration c) {
  configuration = c;
}

/*
 * Returns the current configuration.
 * @return Current configuration.
 */
Configuration Projector::getConfiguration() {
	return(configuration);
}

/*
 * Highlights the background.
 */
void Projector::highlight() {
	if(!highlighted) {
		highlighted = true;
	}
}

/*
 * Disables highlighting of background.
 */
void Projector::unHighlight() {
	if(highlighted) {
		highlighted = false;
	}
}

/*
 * Gets a pointer to the memory location of the buffer used by this certain projector.
 * @param
 * @return
 */
int* Projector::getBuffer() {
	return pnt;
}

/*
 * Displays the view through the projector associated with this instance.
 * Prior to that it will also possibly have applied color settings and
 * definitely applied keystone correction on the view.
 * @param
 * @return
 */
void Projector::display(Scene scene) {
	if(scene.getBackgroundHighlightning())
		glClearColor(0.9,0,0,0);
	else
		glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glClear(GL_DEPTH_BUFFER_BIT);


	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0,1);

	GLuint pid;

	//necessary??
	if(shaders.size()) {
		pid = shaders[0].getShaderProgram();
	}else {
		pid = colorTranslator->getShader()->getShaderProgram();
	}

	glUseProgram(pid);
	colorTranslator->setFactorUniform();

  //Apply keystone correction
  GLuint keystonePos = glGetUniformLocation(pid, "keystone");
  glUniformMatrix4fv(keystonePos, 1, GL_FALSE, keystone.m);

	//Apply camera translation based on projector position
	Vec3 adjustment3D = pos;
	scene.translateCam(adjustment3D);

	scene.setRotation();
	scene.applyRot(pid);
	scene.applyPos(pid);
	ThreeDSpace * space = scene.get3DSpace();

	//Restore previous camera translation
	adjustment3D.x *= -1;
	adjustment3D.y *= -1;
	adjustment3D.z *= -1;
	scene.translateCam(adjustment3D);

	std::vector<GraphicalObject*> goList = space->getObjects();
	for (std::vector<GraphicalObject*>::iterator it = goList.begin(); it != goList.end(); it++) {
		(*it)->applyTransformation(pid);
		(*it)->rotate();
		(*it)->applyRotation(pid);
		//Apply highlight setting
		float val = highlighted ? 1.0f : 0.0f;
		//std::cout << val << std::endl;
		GLuint loc = glGetUniformLocation(colorTranslator->getShader()->getShaderProgram(), "useHighlight");
		glUniform1f(loc, val);

		(*it)->draw();
	}
		
	

	glUseProgram(0);
	glutSwapBuffers();
}


/*
 * Gets the list of in use shaders.
 * @param void;
 * @return std::list<Shader>
 */

std::vector<Shader> Projector::getShaders() {
	return shaders;
}

/*
 * Adds a shader "s" to the list of shaders.
 * @param Shader s, the Shader you want to add to the list.
 * @return void
 */
void Projector::addShader(Shader shader) {
	shaders.push_back(shader);  
}
