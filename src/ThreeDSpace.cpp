#include <vector>

#include <glload/gl_3_3.h>
#include <GL/freeglut.h>

#include "Shared.h"
#include "GraphicalObject.h"
#include "ThreeDSpace.h"

ThreeDSpace::ThreeDSpace() {
  objects.reserve(10);
  Vec3 origin = {0,0,0};
  setOrigin(origin);
}

std::vector<GraphicalObject*> ThreeDSpace::getObjects()
{
  return objects;
}

void ThreeDSpace::addObject(GraphicalObject * obj)
{
  objects.push_back(obj);
}

void ThreeDSpace::setOrigin(Vec3 org)
{
  origin=org;
}

void ThreeDSpace::bindBuffers(){

  for (std::vector<GraphicalObject*>::iterator it = objects.begin(); it != objects.end(); it++) {
    (*it)->bindBufferData();
  }
}


