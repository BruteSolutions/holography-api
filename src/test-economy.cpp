#include <iostream>
#include <list>
#include <string>
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
//#include "FileLoader.h"
#include "Display.h"

Projector * p1, * p2;
Display* displayHandeler;
Scene * defaultScene;
int highlightState = 0;

GraphicalObject * grObj1, *pGO, * grObj2, *grObj3;
std::vector<GraphicalObject*> selGOs;
/*
float vertexData2[] = {
	0.75f, 0.75f, 0.0f, 1.0f,

	0.75f, -0.75f, 0.0f, 1.0f,
	-0.75f, -0.75f, 0.0f, 1.0f,	 
};

float colorData2[] = {

   1.0f, 0.0f, 0.0f, 1.0f,
	 0.0f, 1.0f, 0.0f, 1.0f,
	 0.0f, 0.0f, 1.0f, 1.0f,
};*/

#define FLB -0.5f, -0.5f, 0.5f, 1.0f 
#define FRB 0.5f, -0.5f, 0.5f, 1.0f
#define FLT -0.5f, 0.5f, 0.5f, 1.0f
#define FRT 0.5f, 0.5f, 0.5f, 1.0f

#define BLB -0.5f, -0.5f, -0.5f, 1.0f 
#define BRB 0.5f, -0.5f, -0.5f, 1.0f
#define BLT -0.5f, 0.5f, -0.5f, 1.0f
#define BRT 0.5f, 0.5f, -0.5f, 1.0f


#define LEFT -0.5f, -0.5f, 0.0f, 1.0f
#define RIGHT 0.5f, -0.5f, 0.0f, 1.0f
#define TOP 0.0f, 0.5f, 0.0f, 1.0f
#define REAR 0.0f, 0.0f, -1.0f, 1.0f
float vertexData[] = {
LEFT, RIGHT, TOP,

TOP, LEFT, REAR,

TOP, RIGHT, REAR,

RIGHT, LEFT, REAR,
};

#define GREEN_COLOR 0.75f, 0.75f, 1.0f, 1.0f
#define BLUE_COLOR 0.0f, 0.5f, 0.0f, 1.0f
#define RED_COLOR 1.0f, 0.0f, 0.0f, 1.0f
#define GREY_COLOR 0.8f, 0.8f, 0.8f, 1.0f
#define BROWN_COLOR 0.5f, 0.5f, 0.0f, 1.0f
float colorData[] = {
    GREEN_COLOR, GREEN_COLOR, GREEN_COLOR,

	BLUE_COLOR, BLUE_COLOR, BLUE_COLOR,

	RED_COLOR, RED_COLOR, RED_COLOR,

	BROWN_COLOR, BROWN_COLOR, BROWN_COLOR,
};
int numwindows = 0;
void graphicSettings(){
    //    glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	//glFrontFace(GL_CW);

//	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LEQUAL);

	//glDepthMask(GL_TRUE);
	//glDepthFunc(GL_LEQUAL);
	//glEnable(GL_DEPTH_CLAMP);
        //glDepthRange(0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);
   glDepthRange(0,1);
}
void bindBuffer(){
	defaultScene->get3DSpace()->bindBuffers();
}
void init()
{ // NOT TO SELF, ALL OBJECTS HAS TO BE IN THE scene before any window bindsbufffer redering
  //if an object is added in a later stage, everywindow has to rebind their buffer

	//defaultScene = FileLoader::loadFile("CadTeapot.x3d");
	grObj1 = new GraphicalObject(vertexData, sizeof(vertexData)/4, colorData, sizeof(colorData)/4);
	grObj2 = new GraphicalObject(vertexData, sizeof(vertexData)/4, colorData, sizeof(colorData)/4);
	grObj3 = new GraphicalObject(vertexData, sizeof(vertexData)/4, colorData, sizeof(colorData)/4);
	defaultScene = new Scene();
	defaultScene->get3DSpace()->addObject(grObj1);
	defaultScene->get3DSpace()->addObject(grObj2);
	defaultScene->get3DSpace()->addObject(grObj3);

	//defaultScene->merge(FileLoader::loadFile("CadTeapot.x3d"));
	

	displayHandeler = new Display(); //add a monitor in here

	bindBuffer(); //bind buffer to monitor window
 	//graphicSettings();
	//grObj1 = defaultScene->get3DSpace()->getObjects().at(0);
	//grObj3 = defaultScene->get3DSpace()->getObjects().at(2);
	//std::cout << "antalet floats " << grObj1->getVertexDataSize() << std::endl;
	//std::cout << "antalet bytes " << grObj1->getVertexDataSize()*4 << std::endl;

	defaultScene->selectNext();


	pGO = defaultScene->getSelected().at(0);

	//initial zoom out

	//Flytta bak objekten lite;
	Vec3 zoom = {1,0,-3};
	grObj1->translate(zoom);
	zoom = {-1,0,-3};
	grObj3->translate(zoom);
	zoom = {0,0,-2};
	grObj2->translate(zoom);

	numwindows++;
}

void addProjector(){
	if(defaultScene == NULL){
		std::cout << "ERROR SCENE NOT INITIALIZED";
		exit(1);
	}

	Vec3 pos = {(float) (numwindows*2), 0, 0}, dir = {0, 0, 0};
	displayHandeler->addProjector(new Projector(NULL,0,pos,dir));

	bindBuffer();
	//graphicSettings();
	numwindows++;
}


void display()
{
//	displayHandeler->getMonitor()->display(*defaultScene);
	if(displayHandeler == NULL) fprintf(stderr,"display not initialized\n");
	displayHandeler->display(*defaultScene);
}


void reshape (int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
//do something here to fix shaders
}

bool worldCtrl = false;
void keyboard(unsigned char key, int x, int y)
{
	Vec3 pos;
	switch (key)
	{
	  case 27:
		  glutLeaveMainLoop();
		  return;
	  case 'v':
std::cout << "--------------------------- PRESSED V -------------------- !11!!\n";
std::cout << "--------------------------- TOGGLE CTRL -------------------- !11!!\n";
		worldCtrl = !worldCtrl;
		if(worldCtrl){
std::cout << "--------------------------- Controlling world -------------------- !11!!\n";
		}
		else{
std::cout << "--------------------------- Controlling Obj -------------------- !11!!\n";
		}
		return;
	  case 'a':
std::cout << "--------------------------- PRESSED A -------------------- !11!!\n";
				
		if(!worldCtrl){
		  pos = {-0.05f, 0.0f, 0.0f};		  
		  pGO->translate(pos);
     	}
		else{
		  pos = {0.05f, 0.0f, 0.0f};
		  defaultScene->translateCam(pos);
		}
	fprintf(stderr,"redisplay\n");
			glutPostRedisplay();
		  return;
      case 'd':
std::cout << "--------------------------- PRESSED D -------------------- !11!!\n";
		if(!worldCtrl){
		  pos = {0.05f, 0.0f, 0.0f};
		  pGO->translate(pos);
		}
		else{
		  pos = {-0.05f, 0.0f, 0.0f};
		  defaultScene->translateCam(pos);
		}
		  glutPostRedisplay();
		  return;
      case 'w':
std::cout << "--------------------------- PRESSED W -------------------- !11!!\n";
		if(!worldCtrl){
		  pos = {0.0f, 0.05f, 0.0f};
		  pGO->translate(pos);
		}
		else{
			pos = {0.0f, 0.0f, 0.05f};
		    defaultScene->translateCam(pos);
		}
		  glutPostRedisplay();
		  return;
      case 's':
std::cout << "--------------------------- PRESSED S -------------------- !11!!\n";
		if(!worldCtrl){
		  pos = {0.0f, -0.05f, 0.0f};
		  pGO->translate(pos);
		}
		else {
			pos = {0.0f, 0.0f, -0.05f};
		    defaultScene->translateCam(pos);
		}
		  glutPostRedisplay();
		  return;
      case 'z':
std::cout << "--------------------------- PRESSED Z -------------------- !11!!\n";
		  pos = {0.0f, 0.0f, 0.05f};
		  pGO->translate(pos);
		  glutPostRedisplay();
		  return;
      case 'x':
std::cout << "--------------------------- PRESSED X -------------------- !11!!\n";
		  pos = {0.0f, 0.0f, -0.05f};
		  pGO->translate(pos);
		  glutPostRedisplay();
		  return;
	  case 'y':
std::cout << "--------------------------- PRESSED Y -------------------- !11!!\n";
		defaultScene->angleX -= 0.1f;
		  glutPostRedisplay();

		return;
	  case 'u':
std::cout << "--------------------------- PRESSED U -------------------- !11!!\n";
		defaultScene->angleX += 0.1f;
		  glutPostRedisplay();
		return;

	  case 'h':
std::cout << "--------------------------- PRESSED H -------------------- !11!!\n";
		defaultScene->angleY -= 0.1f;
		  glutPostRedisplay();

		return;
	  case 'j':
std::cout << "--------------------------- PRESSED J -------------------- !11!!\n";
		defaultScene->angleY += 0.1f;
		  glutPostRedisplay();
		return;
	  case 'n':
std::cout << "--------------------------- PRESSED N -------------------- !11!!\n";
		defaultScene->angleZ -= 0.1f;
		  glutPostRedisplay();

		return;
	  case 'm':
std::cout << "--------------------------- PRESSED M -------------------- !11!!\n";
		defaultScene->angleZ += 0.1f;
		  glutPostRedisplay();
		return;
	  case '7':
std::cout << "--------------------------- PRESSED 7 -------------------- !11!!\n";
		pGO->angleX -= 0.1f;
		  glutPostRedisplay();

		return;
	  case '8':
std::cout << "--------------------------- PRESSED 8 -------------------- !11!!\n";
		pGO->angleX += 0.1f;
		  glutPostRedisplay();
		return;

	  case '4':
std::cout << "--------------------------- PRESSED 4 -------------------- !11!!\n";
		pGO->angleY -= 0.1f;
		  glutPostRedisplay();

		return;
	  case '5':
std::cout << "--------------------------- PRESSED 5 -------------------- !11!!\n";
		pGO->angleY += 0.1f;
		  glutPostRedisplay();
		return;
	  case '1':
std::cout << "--------------------------- PRESSED 1 -------------------- !11!!\n";
		pGO->angleZ -= 0.1f;
		  glutPostRedisplay();

		return;
	  case '2':
std::cout << "--------------------------- PRESSED 2 -------------------- !11!!\n";
		pGO->angleZ += 0.1f;
		  glutPostRedisplay();
		return;
	  case 'p':
		defaultScene->selectNext();
		selGOs = defaultScene->getSelected();
		pGO = selGOs.at(0);
		return;
	case '-':
		pGO->scale-=0.05f;
		 glutPostRedisplay();
			  return;

	case '+':
		pGO->scale+=0.05f;
 glutPostRedisplay();
			  return;
      case 'c': //highlights all objects
std::cout << "--------------------------- PRESSED C -------------------- !11!!\n";

		  highlightState = highlightState ? 0 : 1;
		  if(highlightState) {
			displayHandeler->highlight();
		  }
		  else {
		    displayHandeler->unHighlight();
		  }

		  glutPostRedisplay();
		  return;
	}
}

unsigned int defaults(unsigned int displayMode, int &width, int &height) {return displayMode;}
