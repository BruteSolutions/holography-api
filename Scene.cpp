#include <vector>

#include <glload/gl_3_3.h>
#include <GL/freeglut.h>

#include "Shared.h"
#include "GraphicalObject.h"
#include "ThreeDSpace.h"
#include "Scene.h"

Scene::Scene()
{
	cPos = {-1-1,1};
	cDir = {1,1,-1};
	threeDSpace = new ThreeDSpace();
}

ThreeDSpace* Scene::get3DSpace()
{
	return threeDSpace;
}

Vec3 Scene::getCameraPosition()
{
	return cPos;
}
