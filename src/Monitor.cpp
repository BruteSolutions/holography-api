#include <vector>

#include <glload/gl_3_3.h>
#include <GL/freeglut.h>

#include "Shared.h"
#include "GraphicalObject.h"
#include "ThreeDSpace.h"
#include "Shader.h"
#include "Scene.h"
#include "Projector.h"
#include "Monitor.h"


/**
 * Monitor constructor.
 */
Monitor::Monitor()
{
  Vec3 pos = {0,0,0}, dir = {0,0,0};
  proj = new Projector(NULL, 0, pos, dir);
}

/**
 * Monitor destructor.
 */
Monitor::~Monitor()
{
  delete proj;
}
Projector* Monitor::getProjector(){
	return proj;
}
/**
 * Displays a scene.
 * @param scn Scene to display.
 */
void Monitor::display(Scene scn)
{
  proj->display(scn);
}

/**
 * Adds a shader to rendering.
 * @param s Shader to add.
 */
void Monitor::addShader(Shader s)
{
  shaders.push_back(s);
  proj->addShader(s);
}

/**
 * Returns a list of shaders.
 * @return All associated shaders.
 */
std::vector<Shader> Monitor::getShaders()
{
  return(shaders);
}
