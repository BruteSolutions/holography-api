#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <gtk/gtk.h>

#include <glload/gl_3_3.h>

#include "Shared.h"
#include "Shader.h"
#include "GraphicalObject.h"
#include "ThreeDSpace.h"
#include "Scene.h"
#include "ColorTranslator.h"
#include "Projector.h"
//#include "FileLoader.h"
#include "Display.h"

#include "examplewindow.h"
#include <gtkmm/main.h>

#include <iostream>
#include <GL/glut.h>
#include <cstdlib>
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
  1,  1, 0, 1,
 -1, -1, 0, 1,
  1,  1, 0, 1,
  1, -1, 0, 1
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
void file_ok_sel( GtkWidget        *w,
                         GtkFileSelection *fs );
void startFileBrowser();


void init()
{ // NOT TO SELF, ALL OBJECTS HAS TO BE IN THE scene before any window bindsbufffer redering
  //if an object is added in a later stage, everywindow has to rebind their buffer

	//defaultScene = FileLoader::loadFile("CadTeapot.x3d");
	grObj1 = new GraphicalObject(vertexData, sizeof(vertexData)/4, colorData, sizeof(colorData)/4);
	grObj2 = new GraphicalObject(vertexData, sizeof(vertexData)/4, colorData, sizeof(colorData)/4);
	grObj3 = new GraphicalObject(vertexData, sizeof(vertexData)/4, colorData, sizeof(colorData)/4);
	//testObj = new GraphicalObject(testObject, sizeof(testObject)/4, testObjectColor, sizeof(testObjectColor)/4);
	//GraphicalObject * grobj = new GraphicalObject(ny, sizeof(ny)/4, colorData, sizeof(ny)/4);
	defaultScene = new Scene();
	defaultScene->get3DSpace()->addObject(grObj1);
	defaultScene->get3DSpace()->addObject(grObj2);
	defaultScene->get3DSpace()->addObject(grObj3);
//	defaultScene->get3DSpace()->addObject(grobj);
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
	Vec3 zoom = {1.25f,0,-5};
	grObj1->translate(zoom);
	grObj1->setOrigin({-1,-1,0});
//	grobj->translate(zoom);
//	grobj->setOrigin({-1,-1,0});
	zoom = {-1,0,-5};
	grObj3->translate(zoom);
	zoom = {0,0,-4};
	grObj2->translate(zoom);

	defaultScene->get3DSpace()->setOrigin({0,0,4});

	numwindows++;
	
	

}


	//-------------------------------------------------------------------------
	//  Set up the GLUT Menus.
	//-------------------------------------------------------------------------
	void setupMenus ()
	{


		int menIdSub = glutCreateMenu(subMenu);
		  glutAddMenuEntry("Redxcvsdfddddddddddddddddddddddddddddddddddddddddddddddddddddas", 1);
		  glutAddMenuEntry("Blue", 2);
		  glutAddMenuEntry("Green", 3);
		  glutAddMenuEntry("RGB", 4); 
		  
		int menIdMain = glutCreateMenu(menu);
		  glutAddMenuEntry("Rotation On", 1);
		  glutAddMenuEntry("Translation On", 2);
		  glutAddSubMenu("Change Color", menIdSub);
		  glutAddMenuEntry("Quit", 4);
		
		glutAttachMenu(GLUT_RIGHT_BUTTON);
		
		
	
	}

void menu(int value){
	std::cout << "---------------------------------HELLO MOTO!-----------------------------" << std::endl;
	std::cout << "                                 " << value << std::endl;
  if(value == 0){
  }else{
  	std::cout << "Selected " << value <<std::endl;
    primitive=value;
  }
  
  // you would want to redraw now
  glutPostRedisplay();
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
}

void addProjector(){
	if(defaultScene == NULL){
		std::cout << "ERROR SCENE NOT INITIALIZED";
		exit(1);
	}

	Vec3 pos = {(float) (numwindows*1.1f), 0, 0}, dir = {0, 0, 0};
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
		case 3: defaultScene->get3DSpace()->incrementScale(0.05f); glutPostRedisplay(); return;
		case 4: defaultScene->get3DSpace()->incrementScale(-0.05f); glutPostRedisplay(); return;

	};

}
		GtkWidget *filew;
void motion(int x, int y){
	if(leftmousebutton){
		defaultScene->rotateY((float) (x - mouse_x) / 100);
		defaultScene->rotateX((float) (y - mouse_y)/ 100);

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
	//fprintf(stderr,"redisplay\n");
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
		pGO->rotateX(-0.1f);
		  glutPostRedisplay();

		return;
	  case '8':
std::cout << "--------------------------- PRESSED 8 -------------------- !11!!\n";
		pGO->rotateX(0.1f);
		  glutPostRedisplay();
		return;

		case '9':
std::cout << "--------------------------- PRESSED 9 -------------------- !11!!\n";
			pGO->center(defaultScene->getCameraPosition(), {0,0,-2});
			glutPostRedisplay();
			return;

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

		  highlightState = highlightState ? 0 : 1;
		  if(highlightState) {
			displayHandeler->highlight();
		  }
		  else {
		    displayHandeler->unHighlight();
		  }

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
	}
}

void startFileBrowser() {
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
  	return;
}

char * currentfilepath;
unsigned int defaults(unsigned int displayMode, int &width, int &height) {return displayMode;}

/* Get the selected filename and print it to the console */
void file_ok_sel( GtkWidget        *w,
                         GtkFileSelection *fs )
{
	
    currentfilepath = (char *) gtk_file_selection_get_filename (GTK_FILE_SELECTION (fs));
    gtk_widget_destroy(filew);
	//defaultScene->merge(FileLoader::loadFile(currentfilepath));
	gtk_main_quit();
}


