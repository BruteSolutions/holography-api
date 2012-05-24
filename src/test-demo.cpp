#define GTK_ENABLED

#ifndef GTK_ENABLED
#define TRUE 1
#define FALSE 0
#endif

#include <iostream>
#include <list>
#include <string>
#include <vector>
#ifdef GTK_ENABLED
#include <gtk/gtk.h>
#endif
#include <cmath>
#include <glload/gl_3_3.h>

#include "Shared.h"
#include "Shader.h"
#include "GraphicalObject.h"
#include "ThreeDSpace.h"
#include "Scene.h"
#include "ColorTranslator.h"
#include "Projector.h"
#include "FileLoader.h"
#include "Display.h"

#ifdef GTK_ENABLED
//#include "examplewindow.h"
#include <gtkmm/main.h>
#endif

#include <iostream>
#include <GL/glut.h>
#include <cstdlib>

#include "TestCase.h"
#include "TestFramework.h"
#include "TestShader.h"
#include "TestColorTranslator.h"
#include "TestConfiguration.h"
#include "TestMonitor.h"
#include "TestDisplay.h"
#include "TestProjector.h"
//#include "TestFileLoader.h"

using namespace std;

Projector * p1, * p2;
Display* displayHandeler;
Scene * defaultScene;
int highlightState = 0;

GraphicalObject * grObj1, *pGO, * grObj2, *grObj3, *testObj;
std::vector<GraphicalObject*> selGOs;

//--------------------------TEST OBJECT-----------------------------------
#define horRTop 100.0f, 0.2f, -2.0f, 1.0f
#define horRBot 100.0f, -0.2f, -2.0f, 1.0f
#define horLTop -100.0f, 0.2f, -2.0f, 1.0f
#define horLBot -100.0f, -0.2f -2.0f, 1.0f

#define verTopL 0.1f, 100.0f, -2.0f, 1.0f
#define verTopR 0.1f, 100.0f, -2.0f, 1.0f
#define verBotL -0.1f, -100.0f, -2.0f, 1.0f
#define verBotR 0.1f, -100.0f, -2.0f, 1.0f

#define testColor 1.0f, 0.0f, 0.0f, 1.0f

float testObject[] = {
	verTopL, verBotL, verBotR,
	verBotR, verTopR, verTopL,
	
	horRTop, horLTop, horLBot,
	horLBot, horRTop, horRBot,
};

float testObjectColor[] = {
	testColor,testColor,testColor,
	testColor,testColor,testColor,

	testColor,testColor,testColor,
	testColor,testColor,testColor,

};
//--------------------------TEST OBJECT END-----------------------------------

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
float ny[] =  {
 -1, -1, 0, 1,
 -1,  1, 0, 1,
  0,  0, 0, 1,
 0, 0, 0, 1,
  1,  1, 0, 1,
  1, -1, 0, 1
};
float cube[] =  {
 -1, -1, 1, 1, //triangle 1
 -1,  1, 1, 1,
  1,  1, 1, 1,

 -1, -1, 1, 1, //triangle 2
  1,  1, 1, 1,
  1, -1, 1, 1,

  1, -1, -1, 1,
  1,  1, -1, 1,
  1,  1,  1, 1,

  1, -1, -1, 1,
  1,  1,  1, 1,
  1, -1,  1, 1,

 -1,  1, -1, 1,
 -1,  1,  1, 1,
  1,  1,  1, 1,
 
 -1,  1, -1, 1,
  1,  1,  1, 1,
  1,  1, -1, 1,

 -1, -1, -1, 1, //triangle 1
 -1,  1, -1, 1,
  1,  1, -1, 1,

 -1, -1, -1, 1, //triangle 2
  1,  1, -1, 1,
  1, -1, -1, 1,

  -1, -1, -1, 1,
  -1,  1, -1, 1,
  -1,  1,  1, 1,

  -1, -1, -1, 1,
  -1,  1,  1, 1,
  -1, -1,  1, 1,

 -1,  -1, -1, 1,
 -1,  -1,  1, 1,
  1,  -1,  1, 1,
 
 -1,  -1, -1, 1,
  1,  -1,  1, 1,
  1,  -1, -1, 1,

};

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
float colorData2[] = {
  1,  1, 1, 1,
  1,  1, 1, 1,
  1,  1, 1, 1,

  1,  1, 1, 1,
  1,  1, 1, 1,
  1,  1, 1, 1,

  0.75,  0.75, 0.75, 1,
  0.75,  0.75, 0.75, 1,
  0.75,  0.75, 0.75, 1,

  0.75,  0.75, 0.75, 1,
  0.75,  0.75, 0.75, 1,
  0.75,  0.75, 0.75, 1,

  0.8,  0.8, 0.8, 1,
  0.8,  0.8, 0.8, 1,
  0.8,  0.8, 0.8, 1,

  0.8,  0.8, 0.8, 1,
  0.8,  0.8, 0.8, 1,
  0.8,  0.8, 0.8, 1,

  1,  1, 1, 1,
  1,  1, 1, 1,
  1,  1, 1, 1,

  1,  1, 1, 1,
  1,  1, 1, 1,
  1,  1, 1, 1,

  0.75,  0.75, 0.75, 1,
  0.75,  0.75, 0.75, 1,
  0.75,  0.75, 0.75, 1,

  0.75,  0.75, 0.75, 1,
  0.75,  0.75, 0.75, 1,
  0.75,  0.75, 0.75, 1,

  0.8,  0.8, 0.8, 1,
  0.8,  0.8, 0.8, 1,
  0.8,  0.8, 0.8, 1,

  0.8,  0.8, 0.8, 1,
  0.8,  0.8, 0.8, 1,
  0.8,  0.8, 0.8, 1,
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

static int primitive = 0;
void disp(void);
void menu(int a);
void subMenu(int a);
#ifdef GTK_ENABLED
void file_ok_sel(GtkWidget * w, GtkFileSelection * fs);
#endif
void startFileBrowser();
void startMenu();

int runTests()
{
  TestFramework framework;

  framework.addTestCase(new TestShader());
  framework.addTestCase(new TestColorTranslator());
  framework.addTestCase(new TestConfiguration());
  framework.addTestCase(new TestMonitor());
  framework.addTestCase(new TestDisplay());
  framework.addTestCase(new TestProjector());
  //framework.addTestCase(new TestFileLoader());

  if(framework.test()) {
    std::cout << "All tests passed." << std::endl;
    return(0);
  }
  else {
    std::cerr << "Your code is bad and you should feel bad." << std::endl;
    return(1);
  }
}

void init(int argc, char ** argv)
{ // NOT TO SELF, ALL OBJECTS HAS TO BE IN THE scene before any window bindsbufffer redering
  //if an object is added in a later stage, everywindow has to rebind their buffer

  //Run tests and terminate if --test is given
  if(argc == 2 && !strcmp(argv[1], "--test")) {
    exit(runTests());
  }
	std::cout << "Hej1" << std::endl;
	//defaultScene = FileLoader::loadFile("rawformat.bs");
	std::cout << "Hej2" << std::endl;
	defaultScene = FileLoader::loadFile("CadTeapot.x3d");
	//grObj1 = new GraphicalObject(vertexData, sizeof(vertexData)/4, colorData, sizeof(colorData)/4);
	//grObj2 = new GraphicalObject(vertexData, sizeof(vertexData)/4, colorData, sizeof(colorData)/4);
	//grObj3 = new GraphicalObject(vertexData, sizeof(vertexData)/4, colorData, sizeof(colorData)/4);
	//testObj = new GraphicalObject(testObject, sizeof(testObject)/4, testObjectColor, sizeof(testObjectColor)/4);
	//GraphicalObject * grobj = new GraphicalObject(ny, sizeof(ny)/4, colorData, sizeof(ny)/4);
	//GraphicalObject * grobj = new GraphicalObject(cube, sizeof(cube)/4, colorData2, sizeof(cube)/4);
	
	//defaultScene = new Scene();
	//defaultScene->get3DSpace()->addObject(grObj1);
	//defaultScene->get3DSpace()->addObject(grObj2);
	//defaultScene->get3DSpace()->addObject(grObj3);
	//defaultScene->get3DSpace()->addObject(grobj);
//	defaultScene->get3DSpace()->addObject(testObj);
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
	//grObj1->setOrigin({1,1,1});
	//grObj1->translate({4,4,4});
//	grobj->translate(zoom);
	//grobj->setOrigin({0,0,0});
//	grObj2->setOrigin({3,3,3});
	//grObj2->translate({3,3,3});
//	grObj3->setOrigin({2,2,2});
	//grObj3->translate({2,2,2});

	defaultScene->get3DSpace()->setOrigin({0,0,0});

	numwindows++;
	

}

//-------------------------------------------------------------------------
//  Set up the GLUT Menus.
//-------------------------------------------------------------------------
void setupMenus ()
{
  int menIdSub = glutCreateMenu(subMenu);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Blue", 2);
    glutAddMenuEntry("Green", 3);
    glutAddMenuEntry("RGB", 4); 
    
  int menIdMain = glutCreateMenu(menu);
    glutAddMenuEntry("Rotation On", 1);
    glutAddMenuEntry("Translation On", 2);
    glutAddSubMenu("Change Color", menIdSub);
    glutAddMenuEntry("Quit", 4);
  
  glutAttachMenu(GLUT_MIDDLE_BUTTON);
}

void menu(int value){
	std::cout << "---------------------------------HELLO MOTO!-----------------------------" << std::endl;
	std::cout << "                                 " << value << std::endl;
  if(value == 0){
  }
  else{
  	std::cout << "Selected " << value <<std::endl;
    primitive=value;
  }
  
  // you would want to redraw now
  glutPostRedisplay();
  glutPostOverlayRedisplay();
}
void subMenu(int value){
	std::cout << "---------------------------------SUB PRESSED!-----------------------------" << std::endl;
	std::cout << "                                 " << value << std::endl;
  if(value == 0){
  }else{
  	std::cout << "SUB-" << value <<std::endl;
    primitive=value;
  }
  
  // you would want to redraw now
  glutPostRedisplay();
  glutPostOverlayRedisplay();
}

void addProjector(){
	if(defaultScene == NULL){
		std::cout << "ERROR SCENE NOT INITIALIZED";
		exit(1);
	}

	Vec3 pos = {(float) (numwindows*1.05f), 0, -15}, dir = {0, 0, 0};
	//Vec3 pos = {0,0,-10}, dir = {0,0,0};
	displayHandeler->addProjector(new Projector(NULL,0,pos,dir));

	bindBuffer();
	//graphicSettings();
	numwindows++;
}

void display()
{
  //displayHandeler->getMonitor()->display(*defaultScene);
	if(displayHandeler == NULL) fprintf(stderr,"display not initialized\n");
	displayHandeler->display(*defaultScene);
}


void reshape (int w, int h)
{
  //Alt 0: Reshape everything
glViewport(0, 0, (GLsizei) w, (GLsizei) h);
//do something here to fix shaders
/*
//Alt 1: Maximize viewing area
defaultScene->worldPos.m[0] = defaultScene->fFrustumScale / (w / (float)h);
defaultScene->worldPos.m[5] = defaultScene->fFrustumScale;
glViewport(0, 0, (GLsizei) w, (GLsizei) h);
/* //Alt 2: Keep a rectanglish view area
if(w < h)
glViewport(0, 0, (GLsizei) w, (GLsizei) w);
else
glViewport(0, 0, (GLsizei) h, (GLsizei) h);
*/
}

bool leftmousebutton = false;
bool rightmousebutton = false;
bool middlemousebutton = false;
int mouse_x;
int mouse_y;

void mouse(int button, int state, int x, int y) {
	std::cout << "Mouse function" << button << " " << state << " coord ( " << x <<", "<< y << " )"<< std::endl;
	//left mouse button = 0
	//right mouse button = 2
	//middle mouse button = 1
 	//scroll forward = button 3
	//scroll backward = button 4
	mouse_x = x;
	mouse_y = y;
	switch (button)
	{
		case 0: if(state == 0) leftmousebutton = true; else leftmousebutton = false; return;
		case 1: if(state == 0) middlemousebutton = true; else middlemousebutton = false; return;
		case 2: if(state == 0) rightmousebutton = true; else rightmousebutton = false; return;
		case 3: if(state == 0) defaultScene->get3DSpace()->incrementScale(0.05f); glutPostRedisplay(); return;
		case 4: if(state == 0) defaultScene->get3DSpace()->incrementScale(-0.05f); glutPostRedisplay(); return;
	};
}

#ifdef GTK_ENABLED
		GtkWidget *filew;
#endif
int objCtrl = false;
void motion(int x, int y){
	int mod = glutGetModifiers();
	if(leftmousebutton){
		if(objCtrl){
			pGO->rotateY((float) (x - mouse_x) / 100);
			pGO->rotateX((float) (y - mouse_y)/ 100);
		}else{
			if(mod == GLUT_ACTIVE_CTRL){ // THIS DOES NOT WORK IF CAPSLOCK IS ON
				defaultScene->rotateZ((float) (x - mouse_x) / 100);
			} else{
				defaultScene->rotateY((float) (x - mouse_x) / 100);
			}			
			defaultScene->rotateX((float) (y - mouse_y)/ 100);
		}
		glutPostRedisplay();

	}
	if(rightmousebutton){
		Vec3 pos = {(float) (x-mouse_x) / 100, (float) (y-mouse_y) /100, 0.0f};
		    
		defaultScene->translateCam(pos);

		glutPostRedisplay();

	}
		mouse_x = x;
		mouse_y = y;

}
int proj = 0;
int corner = 0;
bool worldCtrl = false;
int keystone = 0;
KeystoneSetting ks[] = { 
{ 1, 1, -1, 1, -1, -1, 1, -1},
{ 0.91, 0.87,-1.01,0.99,-0.98,-0.99,0.9,-0.96},
{ 0.98, 0.97,-1,1,-0.97,-0.98,0.96, -0.98 },
{ 1, 1, -0.97, 0.97, -0.95, -0.98, 0.98, -0.99}};
void keyboard(unsigned char key, int x, int y)
{
	Vec3 pos;
	switch (key)
	{
	  case 'e':
		objCtrl = !objCtrl;
		return;
	  case 'q':
		defaultScene->autoRescale();
		glutPostRedisplay();
		return;
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
	//fprintf(stderr,"redisplay\n");
			glutPostRedisplay();
		  return;
      case 'M':
		//pGO->rotateX(3.14159/2);
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
/*	  case '7':
std::cout << "--------------------------- PRESSED 7 -------------------- !11!!\n";
		pGO->rotateX(-0.1f);
		  glutPostRedisplay();

		return;
	  case '8':
std::cout << "--------------------------- PRESSED 8 -------------------- !11!!\n";
		pGO->rotateX(0.1f);
		  glutPostRedisplay();
		return;
*/
		case '9':
std::cout << "--------------------------- PRESSED 9 -------------------- !11!!\n";
			pGO->center(defaultScene->getCameraPosition(), {0,0,-2});
			glutPostRedisplay();
			return;
/*
	  case '4':
std::cout << "--------------------------- PRESSED 4 -------------------- !11!!\n";
		pGO->rotateY(-0.1f);
		  glutPostRedisplay();

		return;
	  case '5':
std::cout << "--------------------------- PRESSED 5 -------------------- !11!!\n";
		pGO->rotateY(0.1f);
		  glutPostRedisplay();
		return;
	  case '1':
std::cout << "--------------------------- PRESSED 1 -------------------- !11!!\n";
		pGO->rotateZ(-0.1f);;
		  glutPostRedisplay();

		return;
	  case '2':
std::cout << "--------------------------- PRESSED 2 -------------------- !11!!\n";
		pGO->rotateZ(0.1f);
		  glutPostRedisplay();
		return;*/
/*case '1':
	displayHandeler->getProjectors()->at(proj).moveKeystoneCorner(corner, 0, -0.01);
	glutPostRedisplay();
	return;
case '2':
	displayHandeler->getProjectors()->at(proj).moveKeystoneCorner(corner, 0, 0.01);
	glutPostRedisplay();
	return;
case '3':
	displayHandeler->getProjectors()->at(proj).moveKeystoneCorner(corner, 1, -0.01);
	glutPostRedisplay();
	return;
case '4':
	displayHandeler->getProjectors()->at(proj).moveKeystoneCorner(corner, 1, 0.01);
	glutPostRedisplay();
	return;
case '7':
	corner++;
	if(corner == 4) corner = 0;
	return;*/
case '8':
	proj++;
	if(proj >= displayHandeler->getProjectors()->size()) proj = 0;
	return;
	  case 'p':
std::cout << "--------------------------- PRESSED P -------------------- !11!!\n";
		defaultScene->selectNext();
		selGOs = defaultScene->getSelected();
		pGO = selGOs.at(0);
		return;
	case '-':
std::cout << "--------------------------- PRESSED - -------------------- !11!!\n";
		if(!worldCtrl){
			pGO->incrementScale(-0.05f);
		}
		else{			
		    defaultScene->get3DSpace()->incrementScale(-0.05f);
		}		
		 glutPostRedisplay();
		return;

	case '+':
std::cout << "--------------------------- PRESSED + -------------------- !11!!\n";
		if(!worldCtrl){
			pGO->incrementScale(0.05f);
		}
		else{			
		    defaultScene->get3DSpace()->incrementScale(0.05f);
		}		
 		glutPostRedisplay();
		return;
      case 'c': //highlights all objects
std::cout << "--------------------------- PRESSED C -------------------- !11!!\n";
/*
		  highlightState = highlightState ? 0 : 1;
		  if(highlightState) {
			displayHandeler->highlight();
		  }
		  else {
		    displayHandeler->unHighlight();
		  }
*/
		pGO->toggleHighlight();
		glutPostRedisplay();
		return;
	case 'b':
std::cout << "--------------------------- PRESSED B -------------------- !11!!\n";
		pGO->setMesh((!pGO->hasMesh()));
		glutPostRedisplay();
		return;
	case ',':	
std::cout << "--------------------------- PRESSED , -------------------- !11!!\n";
		 startFileBrowser();
		 glutPostRedisplay();
		 return;
	case 'l':	
std::cout << "--------------------------- PRESSED . -------------------- !11!!\n";
		defaultScene->toggleBackgroundHighlightning();
		glutPostRedisplay();
		return;
	case ' ':	
std::cout << "--------------------------- PRESSED space !-------------------- !11!!\n";
		startMenu();
		glutPostRedisplay();
		return;
//predefined keystone settings
case 'k':
	keystone++;
	if(keystone >= 4){
		keystone = 0;
	}
	displayHandeler->getProjectors()->at(proj).setKeystoneObserved(ks[keystone]);
	std::cout << "Keystone setting: " << keystone << " On projector: " << proj << std::endl;

	glutPostRedisplay();
	return;
	}
}





#ifdef GTK_ENABLED
gint button_press (GtkWidget *, GdkEvent *);
void menuitem_response (gchar *);
GtkWidget *window, *window2;
GtkWidget *vbox;
GtkWidget *exit_button;
#endif



void destroyMenu() {
#ifdef GTK_ENABLED
	gtk_widget_destroy(window);
    gtk_widget_destroy (vbox);
    gtk_main_quit();
#endif
}


void startFileBrowser() {
#ifdef GTK_ENABLED
	gtk_init (0, 0);
		
	/* Create a new file selection widget */
	filew = gtk_file_selection_new ("File selection");

	g_signal_connect (filew, "destroy",
			      G_CALLBACK (gtk_main_quit), NULL);
	/* Connect the ok_button to file_ok_sel function */
	g_signal_connect (GTK_FILE_SELECTION (filew)->ok_button,
			  "clicked", G_CALLBACK (file_ok_sel), (gpointer) filew);

	/* Connect the cancel_button to destroy the widget */
	g_signal_connect_swapped (GTK_FILE_SELECTION (filew)->cancel_button,
			              "clicked", G_CALLBACK (gtk_widget_destroy),
				  filew);

	/* Lets set the filename, as if this were a save dialog, and we are giving

	 a default filename */
	gtk_file_selection_set_filename (GTK_FILE_SELECTION(filew), 
					 "penguin.png");

	gtk_widget_show (filew);
	gtk_main ();
  #endif
  	return;
}

char * currentfilepath;
unsigned int defaults(unsigned int displayMode, int &width, int &height) {return displayMode;}

#ifdef GTK_ENABLED
/* Get the selected filename and print it to the console */
void file_ok_sel( GtkWidget *w, GtkFileSelection *fs ) {
	
    currentfilepath = (char *) gtk_file_selection_get_filename (GTK_FILE_SELECTION (fs));
    gtk_widget_destroy(filew);
	defaultScene->merge( FileLoader::loadFile( std::string(currentfilepath) ) );
    displayHandeler->rebindBuffers(defaultScene);
	gtk_main_quit();
}
#endif

void selectNextObject();
void selectNextObject() {
	pGO->setHighlight(FALSE);
	defaultScene->selectNext();
	selGOs = defaultScene->getSelected();
	pGO = selGOs.at(0);
	pGO->setHighlight(TRUE);
	
	destroyMenu();
}

void toggleWorldControl();
void toggleWorldControl() {
	worldCtrl = !worldCtrl;
	std::cout << "World controll now " << worldCtrl << std::endl;
	destroyMenu();
}

void highlightBackground();
void highlightBackground() {
	defaultScene->toggleBackgroundHighlightning();
	glutPostRedisplay();
	destroyMenu();
}

void toggleHighlight();
void toggleHighlight() {
	pGO->toggleHighlight();
	destroyMenu();
}

void centerObject();
void centerObject() {
	Vec3 ori = {-defaultScene->get3DSpace()->getOrigin().x,-defaultScene->get3DSpace()->getOrigin().y,-defaultScene->get3DSpace()->getOrigin().z};
	pGO->center(defaultScene->getCameraPosition(), ori);
	std::cout << "ORINGIN " << defaultScene->get3DSpace()->getOrigin().x << defaultScene->get3DSpace()->getOrigin().y << defaultScene->get3DSpace()->getOrigin().z << std::endl;
	destroyMenu();
}

void toggleMesh();
void toggleMesh() {
	pGO->setMesh(!pGO->hasMesh());
	destroyMenu();
}

const char*  boolToString(bool b);
const char*  boolToString(bool b) {
  return b ? "true" : "false";
}

#ifdef GTK_ENABLED
void enter_callback (GtkWidget *widget, GtkWidget *entry );
void enter_callback( GtkWidget *widget, GtkWidget *entry ) {
	std::cout << gtk_entry_get_text(GTK_ENTRY(entry)) << std::endl;
}
#endif

void startMenu() {
#ifdef GTK_ENABLED
  GtkWidget *menu;
  GtkWidget *menu_bar;
  GtkWidget *root_menu;
  GtkWidget *menu_items;


  GtkWidget *worldCtrl_button, *selectNext_button, *highlightBackground_button, *toggleHighlight_button, *centerObject_button, *toggleMesh_button;
  char buf[128];
  int i;

  gtk_init (0, 0);

  /* create a new window */
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_usize (GTK_WIDGET (window), 400, 300);
  gtk_window_set_title (GTK_WINDOW (window), "GTK Menu Test");
  gtk_signal_connect (GTK_OBJECT (window), "delete_event",
                    (GtkSignalFunc) gtk_main_quit, NULL);

  /* Init the menu-widget, and remember -- never
  * gtk_show_widget() the menu widget!! 
  * This is the menu that holds the menu items, the one that
  * will pop up when you click on the "Root Menu" in the app */
  menu = gtk_menu_new ();
    
  //Create load file menu option
  menu_items = gtk_menu_item_new_with_label ("Load file");  
  gtk_menu_append (GTK_MENU (menu), menu_items);
  gtk_signal_connect_object (GTK_OBJECT (menu_items), "activate",
            GTK_SIGNAL_FUNC (startFileBrowser), (gpointer) g_strdup ("Load file"));
  gtk_widget_show (menu_items);

  /* This is the root menu, and will be the label
  * displayed on the menu bar.  There won't be a signal handler attached,
  * as it only pops up the rest of the menu when pressed. */
  root_menu = gtk_menu_item_new_with_label ("File");

  gtk_widget_show (root_menu);

  /* Now we specify that we want our newly created "menu" to be the menu
  * for the "root menu" */
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (root_menu), menu);

  /* A vbox to put a menu and a button in: */
  vbox = gtk_vbox_new (TRUE, 0);
  gtk_container_add (GTK_CONTAINER (window), vbox);
  gtk_widget_show (vbox);

  /* Create a menu-bar to hold the menus and add it to our main window */
  menu_bar = gtk_menu_bar_new ();
  gtk_box_pack_start (GTK_BOX (vbox), menu_bar, FALSE, FALSE, 2);
  gtk_widget_show (menu_bar);

  /* Create a exit button  */
  exit_button = gtk_button_new_with_label ("Exit");
  gtk_signal_connect_object (GTK_OBJECT (exit_button), "event",
   (GtkSignalFunc) button_press, GTK_OBJECT (window));
  gtk_box_pack_end (GTK_BOX (vbox), exit_button, TRUE, TRUE, 2);
  gtk_widget_show (exit_button);

  /* Toggle worldCtrl button*/
  gchar* _toggled = (gchar*)(worldCtrl ? "Toggle worldCtrl: True" : "Toggle worldCtrl: False");
  worldCtrl_button = gtk_button_new_with_label (_toggled);
  gtk_signal_connect_object (GTK_OBJECT (worldCtrl_button), "clicked",
   (GtkSignalFunc) toggleWorldControl, GTK_OBJECT (window));
  gtk_box_pack_end (GTK_BOX (vbox), worldCtrl_button, TRUE, TRUE, 2);
  gtk_widget_show (worldCtrl_button);

  /* Select next object button*/
  selectNext_button = gtk_button_new_with_label ("Select next object");
  gtk_signal_connect_object (GTK_OBJECT (selectNext_button), "clicked",
   (GtkSignalFunc) selectNextObject, GTK_OBJECT (window));
  gtk_box_pack_end (GTK_BOX (vbox), selectNext_button, TRUE, TRUE, 2); 
  gtk_widget_show (selectNext_button);

  /* Hightlight background button */
   _toggled = (gchar*)(defaultScene->getBackgroundHighlightning() ? "Highlight background: True" : "Highlight background: False");
  highlightBackground_button = gtk_button_new_with_label (_toggled);
  gtk_signal_connect_object (GTK_OBJECT (highlightBackground_button), "clicked",
   (GtkSignalFunc) highlightBackground, GTK_OBJECT (window));
  gtk_box_pack_end (GTK_BOX (vbox), highlightBackground_button, TRUE, TRUE, 2);
  gtk_widget_show (highlightBackground_button);

  /* toggleHighlight_button */
  toggleHighlight_button = gtk_button_new_with_label ("Toggle object highlight");
  gtk_signal_connect_object (GTK_OBJECT (toggleHighlight_button), "clicked",
   (GtkSignalFunc) toggleHighlight, GTK_OBJECT (window));
  gtk_box_pack_end (GTK_BOX (vbox), toggleHighlight_button, TRUE, TRUE, 2);
  gtk_widget_show (toggleHighlight_button);

  /* centerObject_button */
  centerObject_button = gtk_button_new_with_label ("Center object around origin");
  gtk_signal_connect_object (GTK_OBJECT (centerObject_button), "clicked",
   (GtkSignalFunc) centerObject, GTK_OBJECT (window));
  gtk_box_pack_end (GTK_BOX (vbox), centerObject_button, TRUE, TRUE, 2);
  gtk_widget_show (centerObject_button);

  /* toggleMesh_button */
   _toggled = (gchar*)(pGO->hasMesh() ? "Toggle mesh: True" : "Toggle mesh: False");
  toggleMesh_button = gtk_button_new_with_label (_toggled);
  gtk_signal_connect_object (GTK_OBJECT (toggleMesh_button), "clicked",
   (GtkSignalFunc) toggleMesh, GTK_OBJECT (window));
  gtk_box_pack_end (GTK_BOX (vbox), toggleMesh_button, TRUE, TRUE, 2);
  gtk_widget_show (toggleMesh_button);

  /* Create the GtkText widget */
  GtkWidget *entry = gtk_entry_new_with_max_length (50);
  gtk_signal_connect(GTK_OBJECT(entry), "activate", GTK_SIGNAL_FUNC(enter_callback), entry);
  gtk_box_pack_start (GTK_BOX (vbox), entry, TRUE, TRUE, 0);
  gtk_widget_show (entry);
  gtk_entry_set_text (GTK_ENTRY (entry), "Set world origin on the form: x,y,z: current: ");
  char* s;
  asprintf(&s, "%f %f", defaultScene->get3DSpace()->getOrigin().x, defaultScene->get3DSpace()->getOrigin().y);    
  // asprintf(&s, "%.4f,", defaultScene->get3DSpace()->getOrigin().x);    
  // asprintf(&s, "%.4f,", defaultScene->get3DSpace()->getOrigin().y); 
  // asprintf(&s, "%.4f,", defaultScene->get3DSpace()->getOrigin().z); 

  gtk_entry_append_text (GTK_ENTRY (entry), s);


  /* And finally we append the menu-item to the menu-bar -- this is the
  * "root" menu-item I have been raving about =) */
  gtk_menu_bar_append (GTK_MENU_BAR (menu_bar), root_menu);

  /* always display the window as the last step so it all splashes on
  * the screen at once. */
  gtk_widget_show (window);

  gtk_main ();
#endif
}

#ifdef GTK_ENABLED
/* Respond to a button-press by posting a menu passed in as widget.
 *
 * Note that the "widget" argument is the menu being posted, NOT
 * the button that was pressed.
 */

 gint button_press( GtkWidget *widget,
                          GdkEvent *event )
{
	std::cout << "button press---------------------------"<<std::endl;
    if (event->type == GDK_BUTTON_PRESS) {
        GdkEventButton *bevent = (GdkEventButton *) event; 
   //     gtk_menu_popup (GTK_MENU (widget), NULL, NULL, NULL, NULL,
     //                   bevent->button, bevent->time);
     	std::cout << "QUIT---------------------------"<<std::endl;
     	gtk_widget_destroy(window);
     	gtk_widget_destroy (vbox);
     	gtk_main_quit();
        /* Tell calling code that we have handled this event; the buck
         * stops here. */
        return TRUE;
    }

    /* Tell calling code that we have not handled this event; pass it on. */
    return FALSE;
}


/* Print a string when a menu item is selected */

 void menuitem_response( gchar *string )
{
    printf ("%s\n", string);
}

#endif
