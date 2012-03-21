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

float vertexData[] = {
	0.75f, 0.75f, 0.0f, 1.0f,
	0.75f, -0.75f, 0.0f, 1.0f,
	-0.75f, -0.75f, 0.0f, 1.0f,	 
};

float colorData[] = {
   1.0f, 0.0f, 0.0f, 1.0f,
	 0.0f, 1.0f, 0.0f, 1.0f,
	 0.0f, 0.0f, 1.0f, 1.0f,
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
  //Create shader and push to one of the projectors
  p1->addShader(Shader("AdjustPosition.vert", "IdFragment.frag"));
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
  //TODO: Remove
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
