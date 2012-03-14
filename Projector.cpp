#include <list>
#include "Projector.h"

/*
 * Creates a new projector with buffer of size len at the place pointer with position pos
 * and direction dir;
 */
Projector::Projector(int * pointer, unsigned int len, Vec3 pos, Vec3 dir) : highlighted(false) 
{
	colorTranslator = new ColorTranslator(); //Creates a ColorTranslator with default values.
	pnt = pointer;
	bufferSize = len;
	setPosition(pos);
	setDirection(dir);
	//create necessary Shader objects => hardcode a picture for the buffer. How do I do that?
}

/*
 * Creates a new projector with buffer of size len at the place pointer with position (0,0,0)
 * and direction (0,0,0);
 */
Projector::Projector(int * pointer, unsigned int len)
{
	Projector(pointer, len, new Vec3(0, 0, 0), new Vec3 (0, 0, 0));

}
/*
 * Sets the position of the projector to the value of the parametre.
 * @param The new position of the projector.
 */
void Projector::setPosition(Vec3 pos)
{
	this.pos = pos;
}

/*
 * Returns the position of the projector as a Vec3 object.
 * @return the position of the projector
 */
Vec3 Projector::getPosition()
{
	return pos;
}

/*
 * Sets the direction of the projectior to the parametre.
 * @param The new direction of the projector
 */
void Projector::setDirection(Vec3 dir)
{
	this.dir = dir;
}

/*
 * Returns the direction of the projector as a Vec3 object.
 * @return the direction of the projector
 */
Vec3 Projector::getDirection()
{
	return dir;
}

/*
 * Returns the size of the buffer.
 * @return Size of the buffer.
 */
unsigned int Projector::getBufferSize()
{
  return(bufferSize);
}

/*
  Returns the associated colortranslator object.
 * @return Colortranslator object.
 */
ColorTranslator Projector::getColorTranslator()
{
  return(colorTranslator);
}

/*
 * Set the current configuration.
 * @param c Configuration to be used.
 */
void Projector::setConfiguration(Configuration c)
{
  configuration = c;
}

/*
 * Returns the current configuration.
 * @return Current configuration.
 */
Configuration Projector::getConfiguration()
{
  return(configuration);
}

/*
 * Highlights the background.
 */
void Projector::highlight()
{
  if(!highlight) {
    highlight = true;
    //TODO: Add
  }
}

/*
 * Disables highlighting of background.
 */
void Projector::unHighlight()
{
  if(highlight) {
    highlight = false;
    //TODO: Remove
  }
}

/*
 * Gets a pointer to the memory location of the buffer used by this certain projector.
 * @param
 * @return
 */
int* Projector::getBuffer()
{
	return &buffer;
}

/*
 * Displays the view through the projector associated with this instance.
 * Prior to that it will also possibly have applied color settings and
 * definitely applied keystone correction on the view.
 * @param
 * @return
 */
void Projector::display (Scene scn)
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  //TODO: Do color settings

  3Dspace space = scn.get3DSpace();
  std::list<GraphicalObject> goList = space.getObjects(); // I need a list to do for each.

  for (std::list<GraphicalObject>::iterator it = goList.begin(); goList != fifth.end(); goList++) {
    if(map.containsKey(*it.id)) {
      //TODO: Apply associated shaders
    }
  }

  //TODO: Perform keystone correction
  
  glutSwapBuffers();
}

/*
 * Gets the list of in use shaders.
 * @param void;
 * @return std::list<Shader>
 */

std::list<Shader> Projector::getShaders()
{
  return shaders;
}

/*
 * Adds a shader "s" to the list of shaders.
 // * This might endlessly grow, to later crash the program?
 // * Due to the fact that there is no way to effectivly remove shaders.
 * @param Shader s, the Shader you want to add to the list.
 * @return void
 */
void Projector::addShader(Shader s)
{
  shaders.add(s);  
}
