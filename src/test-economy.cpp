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
GraphicalObject * grObj1;
/* OLD OBJECT
float vertexData[] = {
	0.75f, 0.75f, 0.0f, 1.0f,
	0.75f, -0.75f, 0.0f, 1.0f,
	-0.75f, -0.75f, 0.0f, 1.0f,	 
};

float colorData[] = {
   1.0f, 0.0f, 0.0f, 1.0f,
	 0.0f, 1.0f, 0.0f, 1.0f,
	 0.0f, 0.0f, 1.0f, 1.0f,
};*/

#define LEFT -0.5f, -0.5f, 0.0f, 1.0f
#define RIGHT 0.5f, -0.5f, 0.0f, 1.0f
#define TOP 0.0f, 0.5f, 0.0f, 1.0f
#define REAR 0.0f, 0.0f, -0.05f, 1.0f
float vertexData1[] = {
LEFT, RIGHT, TOP,

TOP, LEFT, REAR,

TOP, RIGHT, REAR,

RIGHT, LEFT, REAR,

/* 0.0f, 0.5f, 0.0f, 1.0f,
0.5f, -0.366f, 0.0f, 1.0f,
-0.5f, -0.366f, 0.0f, 1.0f,
0.0f, 0.5f, 0.0f, 1.0f,
0.5f, -0.366f, 0.0f, 1.0f,
0.0f, 0.2f, -0.4f, 1.0f,
0.5f, -0.366f, 0.0f, 1.0f,
-0.5f, -0.366f, 0.0f, 1.0f,
0.0f, 0.2f, -0.4f, 1.0f,
0.0f, 0.5f, 0.0f, 1.0f,
-0.5f, -0.366f, 0.0f, 1.0f,
0.0f, 0.2f, -0.4f, 1.0f,*/
};

#define GREEN_COLOR 0.75f, 0.75f, 1.0f, 1.0f
#define BLUE_COLOR 0.0f, 0.5f, 0.0f, 1.0f
#define RED_COLOR 1.0f, 0.0f, 0.0f, 1.0f
#define GREY_COLOR 0.8f, 0.8f, 0.8f, 1.0f
#define BROWN_COLOR 0.5f, 0.5f, 0.0f, 1.0f
float colorData1[] = {
    GREEN_COLOR, GREEN_COLOR, GREEN_COLOR,

	BLUE_COLOR, BLUE_COLOR, BLUE_COLOR,

	RED_COLOR, RED_COLOR, RED_COLOR,

	BROWN_COLOR, BROWN_COLOR, BROWN_COLOR,
};

void init()
{
  defaultScene = new Scene();
  grObj1 = new GraphicalObject(vertexData, sizeof(vertexData), colorData, sizeof(colorData));
  defaultScene->get3DSpace()->addObject(grObj1);
}

void init1()
{
  Vec3 pos = {0, 0, 0}, dir = {0, 0, 0};
  p1 = new Projector(NULL, 0, pos, dir);
  defaultScene->get3DSpace()->getObjects()[0]->bindBufferData();
}

void init2()
{
  Vec3 pos = {2, 0, 0}, dir = {0, 0, 0};
  p2 = new Projector(NULL, 0, pos, dir);
  defaultScene->get3DSpace()->getObjects()[0]->bindBufferData();
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
	switch (key)
	{
	  case 27:
		  glutLeaveMainLoop();
		  return;
	}
}

unsigned int defaults(unsigned int displayMode, int &width, int &height) {return displayMode;}
