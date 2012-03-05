#include "Projector.h"


/* *Shader*() - Does not compute.
 * Shall I make a call to the shader class
 * or something?
 * The ADD Document does nothing for me here.
 */


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

// Do Keystone Correction

// Get View for this projector.
}