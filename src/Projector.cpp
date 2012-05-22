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

using namespace std;

/**
 * Creates a new projector with a buffer of size len at the place pointer with position pos and direction dir;
 */
Projector::Projector(int * pointer, unsigned int len, Vec3 pos, Vec3 dir) :
  highlighted(false), configuration(pos, dir, {0.5, 0.5, 0.5}) {
	colorTranslator = new ColorTranslator(); //Creates a ColorTranslator with default values.
	pnt = pointer;
	bufferSize = len;
	setPosition(pos);
	setDirection(dir);
  X1 = 1;
  X2 = -1;
  X3 = -1;
  X4 = 1;
  Y1 = 1;
  Y2 = 1;
  Y3 = -1;
  Y4 = -1;

  memset(keystone.m, 0, sizeof(keystone.m));
  for(int i = 0; i < 16; i += 5) {
    keystone.m[i] = 1.0;
  }
}

/**
 * Creates a new projector with buffer of size len at the place pointer with position (0,0,0)
 * and direction (0,0,0);
 */
Projector::Projector(int * pointer, unsigned int len) :
  configuration({0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.5, 0.5, 0.5}) { 
	Vec3 pos = {0,0,0}, dir = {0,0,0};
	Projector(pointer, len, pos, dir);
}
void Projector::setKeystoneObserved(KeystoneSetting f){
    X1 = f.k[0];
    Y1 = f.k[1];
    X2 = f.k[2];
    Y2 = f.k[3];
    X3 = f.k[4];
    Y3 = f.k[5];
    X4 = f.k[6];
    Y4 = f.k[7];
}

/**
 * An interface to move the corners of the projected image, changing the observed
 * values so that a new Keystone matrix can be calculated. 
 * @param corner Which of the four coners to change
 * @param xory States which component of the coordinate of a corner that should be changed X=0 Y=1
 * @param value Is the value to increase or decrease the component with
 */
void Projector::moveKeystoneCorner(int corner, int xory, float value){

	if(xory == 0){ //x
		switch(corner){
			case 0: X1 += value; return;
			case 1: X2 += value; return;
			case 2: X3 += value; return;
			case 3: X4 += value; return;
      default: break;
		}
	}else{
		switch(corner){
			case 0: Y1 += value; return;
			case 1: Y2 += value; return;
			case 2: Y3 += value; return;
			case 3: Y4 += value; return;
      default: break;
		}
	}
} 

/**
 * Calculates the the keystone matrix and sets a uniform
 * @param pid is the shader program used when drawing
 */
void Projector::calcKeystone(GLuint pid) throw (std::string){
		/* The real values */
    float x1= 1, y1=1;
    float x2=-1, y2=1;
    float x3=-1, y3=-1;
    float x4= 1, y4=-1;
//for(int i = 0; i < 8; i++){
	std::cout << "X1: " << X1 << "X2: " << X2 << "X3: " << X3 << "X4: " << X4 <<
 "Y1: " << Y1 << "Y2: " << Y2 << "Y3: " << Y3 << "Y4: " << Y4 << std::endl;
//}
		/* X1-X4, Y1-Y4 are observed values */

    float A [9][9] = { 
    {x1,y1,1,0,0,0,-x1*X1,-y1*X1,-X1},
    {0,0,0,x1,y1,1,-x1*Y1,-y1*Y1,-Y1},
    {x2,y2,1,0,0,0,-x2*X2,-y2*X2,-X2},
    {0,0,0,x2,y2,1,-x2*Y2,-y2*Y2,-Y2},
    {x3,y3,1,0,0,0,-x3*X3,-y3*X3,-X3},
    {0,0,0,x3,y3,1,-x3*Y3,-y3*Y3,-Y3},
    {x4,y4,1,0,0,0,-x4*X4,-y4*X4,-X4},
    {0,0,0,x4,y4,1,-x4*Y4,-y4*Y4,-Y4},
    {0,0,0,0 , 0,0,     0,     0,  1}
    };
    
    float b [9] = { 0,0,0,0,0,0,0,0,1};
    
		/* Perform a Gauss Jordan to solve the system A h = b*/
    for(int j=0;j<9;j++){
        int count = j;
        while(count<9 && A[count][j]==0){
            count++;
        }
	if(count == 9){
		throw "InvalidKeystoneSettingException";
	}
        for(int i=0;i<9;i++){
            float tmp;
            tmp=A[j][i];
            A[j][i]=A[count][i];
            A[count][i]=tmp;
        }
        
        float divisor = A[j][j]; 
        for(int i=0;i<9;i++){
            A[j][i] /= divisor;
        }
        
        for(int i=j+1;i<9;i++){
            float factor = -A[i][j];
            //Fixa rad i
            for(int k=0;k<9;k++){
                A[i][k] += factor*A[j][k];
            }
        }
    }

    for(int j=8;j>=0;j--){
        for(int i=j+1;i<=8;i++){
            b[j] += -b[i]*A[j][i];
        }
    }

    float h33 = 1;
    if(b[6]>0)
        h33 -=b[6];
    else
        h33 +=b[6];
    if(b[7]>0)
        h33 -=b[7];
    else
        h33 +=b[7];

		/* the matrix responsible for the keystone effect (beware, this is the transponate of the matrix)*/
    float h[16] = { b[0], b[3], 0, b[6], b[1], b[4], 0, b[7], 0, 0, h33, 0, b[2], b[5], 0 , 1 };

    /* set the keystone uniform */
    GLuint keystoneLoc = glGetUniformLocation(pid, "keystone");
    glUniformMatrix4fv(keystoneLoc , 1, GL_FALSE, h);
}

/**
 * Sets the position of the projector to the value of the parametre.
 * @param The new position of the projector.
 */
void Projector::setPosition(Vec3 position) {
	pos = position;
}

/**
 * Returns the position of the projector as a Vec3 object.
 * @return the position of the projector
 */
Vec3 Projector::getPosition() {
	return pos;
}

/**
 * Sets the direction of the projectior to the parametre.
 * @param The new direction of the projector
 */
void Projector::setDirection(Vec3 _direction) {
	direction = _direction;
}

/**
 * Returns the direction of the projector as a Vec3 object.
 * @return the direction of the projector
 */
Vec3 Projector::getDirection() {
	return direction;
}

/**
 * Returns the size of the buffer.
 * @return Size of the buffer.
 */
unsigned int Projector::getBufferSize() {
	return(bufferSize);
}

/**
 * Returns the associated colortranslator object.
 * @return Colortranslator object.
 */
ColorTranslator * Projector::getColorTranslator() {
	return(colorTranslator);
}

/**
 * Set the current configuration.
 * @param c Configuration to be used.
 */
void Projector::setConfiguration(Configuration c) {
  configuration = c;
}

/**
 * Returns the current configuration.
 * @return Current configuration.
 */
Configuration Projector::getConfiguration() {
	return(configuration);
}

/**
 * Highlights the background.
 */
void Projector::highlight() {
	if(!highlighted) {
		highlighted = true;
	}
}

/**
 * Disables highlighting of background.
 */
void Projector::unHighlight() {
	if(highlighted) {
		highlighted = false;
	}
}

/**
 * Displays the view through the projector associated with this instance.
 * Prior to that it will also possibly have applied color settings and
 * definitely applied keystone correction on the view.
 * @param takes a scene and draws in the current window
 */
void Projector::display(Scene scene) {
  /* Draw the background */
	if(scene.getBackgroundHighlightning())
		glClearColor(0.9,0,0,0);
	else
		glClearColor(0,0,0,0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0,1);

	GLuint pid;

	/* Fetch the shader program to use */
	if(shaders.size()) {
		pid = shaders[0].getShaderProgram();
	}else {
		pid = colorTranslator->getShader()->getShaderProgram();
	}
	glUseProgram(pid);
	
	/* Sets the factor which decides how the color components affects the red end color */
	colorTranslator->setFactorUniform();

	/* Calculate keystone and set the uniform */
	calcKeystone(pid);

	//Apply camera translation based on projector position
	Vec3 adjustment3D = pos;
	scene.translateCam(adjustment3D);

	/* Calculate world rotation and position */
	scene.setRotation();
	scene.applyRot(pid);
	scene.applyPos(pid);

	//Restore previous camera translation
	adjustment3D.x *= -1;
	adjustment3D.y *= -1;
	adjustment3D.z *= -1;
	scene.translateCam(adjustment3D);

	//Iterate over every graphical object in the scene and draw them in the current window
	ThreeDSpace * space = scene.get3DSpace();
	std::vector<GraphicalObject*> goList = space->getObjects();
	for (std::vector<GraphicalObject*>::iterator it = goList.begin(); it != goList.end(); it++) {
		(*it)->applyTransformation(pid);
		(*it)->rotate(); /* calculates the rotation matrices */
		(*it)->applyRotation(pid); /* sets the rotation uniforms and links matrices */
		(*it)->setHighlightUniform(pid);
		(*it)->draw();
	}
		
	glUseProgram(0);
	glutSwapBuffers();
}


/**
 * Gets the list of in use shaders.
 * @return A list of shaders used by the projector
 */
std::vector<Shader> Projector::getShaders() {
	return shaders;
}

/**
 * Adds a shader object to the list of shaders.
 * @param shader the shader to add to the list.
 */
void Projector::addShader(Shader shader) {
	shaders.push_back(shader);  
}
