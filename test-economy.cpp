#include <iostream>
#include <list>
#include <string>
#include <vector>
#include "glload/include/glload/gl_3_3.h"
#include <GL/freeglut.h>

#include "Shared.h"
#include "Projector.h"
//#include "Scene.h"

Projector * p1, * p2;
Scene * defaultScene;

void init()
{
  std::cout << "Initializing" << std::endl;

  Vec3 pos = {0, 0, 0}, dir = {0, 0, 0};
  p1 = new Projector(NULL, 0, pos, dir);
  p2 = new Projector(NULL, 0, pos, dir);
  defaultScene = NULL;
}

void display() {}

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
