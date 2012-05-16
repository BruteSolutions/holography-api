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
void Projector::add(int corner, int xory, float value){
	std::cout << "corner " << corner << std::endl;
	if(xory == 0){ //x
		std::cout << "X" << std::endl;
		switch(corner){
			case 0: X1 += value; return;
			case 1: X2 += value; return;
			case 2: X3 += value; return;
			case 3: X4 += value; return;
			default: std::cout << "corner " << corner << std::endl; return;
		}
	}else{
		std::cout << "Y" << std::endl;
		switch(corner){
			 
			case 0: Y1 += value; std::cout << " minimizing Y " << std::endl; return;
			case 1: Y2 += value; return;
			case 2: Y3 += value; return;
			case 3: Y4 += value; return;
			default: std::cout << "corner " << corner << std::endl; return;
		}
	}
} 
void Projector::calcKeystone(GLuint pid){
    float x1= 1, y1=1;
    //X1= 1, Y1=1;
    float x2=-1, y2=1;
    //X2=-1, Y2=1;//0.95;
    float x3=-1, y3=-1;
    //X3=-1, Y3=-1;//0.95;
    float x4= 1, y4=-1;
    //X4= 1, Y4=-1;
std::cout << "X1: " << X1;
std::cout << " X2: " << X2;
std::cout << " X3: " << X3;
std::cout << " X4: " << X4;
std::cout << " Y1: " << Y1;
std::cout << " Y2: " << Y2;
std::cout << " Y3: " << Y3;
std::cout << " Y4: " << Y4 << std::endl;

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
    }; //Matrisen
    float A2[9][9];
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            A2[i][j] = A[i][j];
        }
    }

    float b [9] = { 0,0,0,0,0,0,0,0,1};
/*    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            cout<<A[i][j]<<"\t";
        }
        cout<<endl;
    }

    cout<<endl<<endl;
  */ 
    // Observera att denna version inte tar hänsyn till b vektorn
    // Dock så spelar det ingen roll eftersom den bara består av 0or
    // och en etta, men den ettan har redan en rad med en ledande etta
    // så den kommer inte behöva någon redigering så 1an kommer inte heller
    // sprida sig till andra rader.
    for(int j=0;j<9;j++){
        int count = j;
        while(count<9 && A[count][j]==0){
            count++;
        }
  /*      if(count==9){
            cout<<"GaussJordan går inte eftersom det inte går"
            <<endl<<"att reducera matrisen A till identitetsmatrisen";
            //Någon form av felhantering ska in här
            break;
        }
        cout<<count<<endl;*/

        //Byt rad på j:te raden och count:te raden
        //Innebär att att A[j][j] blir en ickenolla
        for(int i=0;i<9;i++){
            float tmp;
            tmp=A[j][i];
            A[j][i]=A[count][i];
            A[count][i]=tmp;
        }
        
        //Dividera så att man får en ledande etta på diagonalen
        float divisor = A[j][j]; 
        for(int i=0;i<9;i++){
            A[j][i] /= divisor;
        }
        
        //Subtrahera så att det bara är ettor under 1:an på A[j][j]
        //För att göra det så måste man subrahera rader från varandra
        //Så därför blir det en nestlad loop
        for(int i=j+1;i<9;i++){
            float factor = -A[i][j];
            //Fixa rad i
            for(int k=0;k<9;k++){
                A[i][k] += factor*A[j][k];
            }
        }
    }

    //Istället för GuassJordan så är det enklare med bara Gauss så
    //Kör på det istället. Så nu så ersätter vi värdena i b en efter en
    //Med start längst ner där det står att b[9]=1
    for(int j=8;j>=0;j--){
        for(int i=j+1;i<=8;i++){
            b[j] += -b[i]*A[j][i];
        }
    }
/*
    for(int i=0;i<9;i++){
        cout<<b[i]<<" ";
    }
    cout<<endl;

    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            cout<<A[i][j]<<"\t";
        }
        cout<<endl;
    }
*/
    float h33 = 1;
    if(b[6]>0)
        h33 -=b[6];
    else
        h33 +=b[6];
    if(b[7]>0)
        h33 -=b[7];
    else
        h33 +=b[7];

/*    cout<<endl<<"H"
    <<endl<< b[0] << " " << b[1] << " 0 " << b[2]
    <<endl<< b[3] << " " << b[4] << " 0 " << b[5]
    <<endl<< "0 0 " << h33 << " 0"
    <<endl<< b[6] << " " << b[7] << " 0 " << "1";//Sista är gissningsvisst h44
    cout<<endl;
/*    float h[4][4] = { { b[0], b[1], 0, b[2] },
			{ b[3], b[4], 0 , b[5]},
			{ 0, 0, h33, 0 },
			{ b[6], b[7], 0, 1}};*/
//float h[16] = { b[0], b[1], 0, b[2], b[3], b[4], 0 , b[5], 0, 0, h33, 0, b[6], b[7], 0, 1 };

float h[16] = { b[0], b[3], 0, b[6], b[1], b[4], 0, b[7], 0, 0, h33, 0, b[2], b[5], 0 , 1 };
GLuint keystoneLoc = glGetUniformLocation(pid, "keystone");
glUniformMatrix4fv(keystoneLoc , 1, GL_FALSE, h);
/*    cout<<"Rader: ";

    for(int i=0;i<9;i++){
        float sum = 0;
        for(int j=0;j<9;j++){
            sum += b[j]*A2[i][j];
        }
        cout << sum << " ";
    }
    cout<<endl;
*/
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

	calcKeystone(pid);
  //Apply keystone correction
//  GLuint keystonePos = glGetUniformLocation(pid, "keystone");
//  glUniformMatrix4fv(keystonePos, 1, GL_FALSE, keystone.m);

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
		(*it)->setHighlightUniform(pid);
		//Apply highlight setting
		//float val = highlighted ? 1.0f : 0.0f;
		
		//std::cout << val << std::endl;
		//GLuint loc = glGetUniformLocation(colorTranslator->getShader()->getShaderProgram(), "useHighlight");
		//glUniform1f(loc, val);

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