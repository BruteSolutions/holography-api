#include "Projector.h"


//TODO:dummy
Projector::Projector()
{
}

/*
 * bla
 * @param
 * @return
 */
unsigned int Projector::getBufferSize()
{
}

/*
 * bla
 * @param
 * @return
 */
ColorTranslator Projector::getColorTranslator()
{
}

/*
 * bla
 * @param
 * @return
 */
void Projector::setConfiguration(Configuration c)
{
}

/*
 * bla
 * @param
 * @return
 */
Configuration Projector::getConfiguration()
{
}

/*
 * bla
 * @param
 * @return
 */
void Projector::highlight()
{
}

/*
 * bla
 * @param
 * @return
 */
void Projector::unHighlight()
{
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
void display (Scene scn)
{
// Do color settings

/*

apply correct shader(s) with data of scn as input

3DSpace tds = scn.get3DSpace();
apply correct shader(s) with data of tds as input

for each(GraphicalObject g in tds):
if(!map.containsKey(g.id)) associate it with a (possibly new) shader-object
{
apply correct shader(s) with data of g as input
apply ColorTranslator’s shader with data of g as input
}
call OpenGL-function to swap buffer;
  
Do Keystone Correction
*/

// Get View for this projector.
}

/*
 * Gets the list of in use shaders.
 * @param void;
 * @return std::list<Shader>
 */

std::list<Shader> getShaders()
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
void addShader(Shader s)
{
  shaders.add(s);  
}
