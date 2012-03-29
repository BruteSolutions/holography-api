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

Projector * p1, * p2;
Scene * defaultScene;
int highlightState = 0;

GraphicalObject * grObj1, * grObj2;


float vertexData2[] = {
	0.75f, 0.75f, 0.0f, 1.0f,
	0.75f, -0.75f, 0.0f, 1.0f,
	-0.75f, -0.75f, 0.0f, 1.0f,	 
};

float colorData2[] = {
   1.0f, 0.0f, 0.0f, 1.0f,
	 0.0f, 1.0f, 0.0f, 1.0f,
	 0.0f, 0.0f, 1.0f, 1.0f,
};

#define LEFT -0.5f, -0.5f, 0.0f, 1.0f
#define RIGHT 0.5f, -0.5f, 0.0f, 1.0f
#define TOP 0.0f, 0.5f, 0.0f, 1.0f
#define REAR 0.0f, 0.0f, -0.05f, 1.0f
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

void init()
{
  defaultScene = new Scene();
  grObj1 = new GraphicalObject(vertexData, sizeof(vertexData), colorData, sizeof(colorData));
  grObj2 = new GraphicalObject(vertexData2, sizeof(vertexData2), colorData2, sizeof(colorData2));

  defaultScene->get3DSpace()->addObject(grObj1);
  defaultScene->get3DSpace()->addObject(grObj2);

}

void init1()
{
  Vec3 pos = {0, 0, 0}, dir = {0, 0, 0};
  p1 = new Projector(NULL, 0, pos, dir);
  defaultScene->get3DSpace()->bindBuffers();
  //Create shader and push to one of the projectors
}

void init2()
{
  Vec3 pos = {2, 0, 0}, dir = {0, 0, 0};
  p2 = new Projector(NULL, 0, pos, dir);
  defaultScene->get3DSpace()->bindBuffers();
}

void display1()
{
  p1->display(*defaultScene);
}

void display2()
{
  p2->display(*defaultScene);
}

void reshape (int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void keyboard(unsigned char key, int x, int y)
{
	Vec3 pos;
	switch (key)
	{
	  case 27:
		  glutLeaveMainLoop();
		  return;
	  case 'a':
std::cout << "--------------------------- PRESSED A -------------------- !11!!\n";
		  pos = {-0.05f, 0.0f, 0.0f};
		  grObj2->translate(pos);
     	  glutPostRedisplay();
		  return;
      case 'd':
std::cout << "--------------------------- PRESSED D -------------------- !11!!\n";
		  pos = {0.05f, 0.0f, 0.0f};
		  grObj2->translate(pos);
		  glutPostRedisplay();
		  return;
      case 'w':
std::cout << "--------------------------- PRESSED W -------------------- !11!!\n";
		  pos = {0.0f, 0.05f, 0.0f};
		  grObj2->translate(pos);
		  glutPostRedisplay();
		  return;
      case 's':
std::cout << "--------------------------- PRESSED S -------------------- !11!!\n";
		  pos = {0.0f, -0.05f, 0.0f};
		  grObj2->translate(pos);
		  glutPostRedisplay();
		  return;
      case 'z':
std::cout << "--------------------------- PRESSED Z -------------------- !11!!\n";
		  pos = {0.0f, 0.0f, 0.05f};
		  grObj1->translate(pos);
		  glutPostRedisplay();
		  return;
      case 'x':
std::cout << "--------------------------- PRESSED X -------------------- !11!!\n";
		  pos = {0.0f, 0.0f, -0.05f};
		  grObj1->translate(pos);

      highlightState = highlightState ? 0 : 1;
      if(highlightState) {
        p1->highlight();
        p2->highlight();
      }
      else {
        p1->unHighlight();
        p2->unHighlight();
      }

		  glutPostRedisplay();
		  return;
	}
}

unsigned int defaults(unsigned int displayMode, int &width, int &height) {return displayMode;}
