#include <iostream>
#include <vector>
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include "Display.h"
#include "Scene.h"
#include "Monitor.h"
#include "Projector.h"

/**
 * Initiates the associated objects.
 */
Display::Display() {
	monitor = new Monitor();
	projectorList = new std::vector<Projector>();

	//COLORTRANSLATOR??
	colorTranslator = new ColorTranslator();
}

/**
 * Displays the given scene.
 * @param scene Scene to display.
 */
void Display::display(Scene scene) {
	//save the current window
	int currentWindow = glutGetWindow();

	//draw monitor
	glutSetWindow(1); //monitor
	monitor->display(scene);

	//draw projectors
	int windowBuffer = 2;
	for (std::vector<Projector>::iterator it = projectorList->begin(); it != projectorList->end(); it++) {
		glutSetWindow(windowBuffer);
		(*it).display(scene);
		windowBuffer++;
	}
	
	glutSetWindow(currentWindow);
	//change back to the current window
}

/**
 * Retrieves all associated projectors.
 * @return All projectors.
 */
std::vector<Projector>* Display::getProjectors(){
	return projectorList;
}

/**
 * Adds a projector to the display.
 * @param projector Projector to be added.
 */
void Display::addProjector(Projector *projector){
	if(projector != NULL){
		projectorList->push_back(*projector);
	}
}

/**
 * Retrieves the associated monitor.
 * @return Current monitor.
 */
Monitor* Display::getMonitor() {
	return monitor;
}

/**
 * Retrieves the current colortranslator.
 * @return The current colortranslator.
 */
ColorTranslator* Display::getColorTranslator() {
	return colorTranslator;
}

/**
 * Retrieves the current bounding cube.
 * @return Current bounding cube.
 */
double Display::getBoundingCube() {
	//todo
}

/**
 * Highlights the display.
 */
void Display::highlight(){
	monitor->getProjector()->highlight();
	for (std::vector<Projector>::iterator it = projectorList->begin(); it != projectorList->end(); it++) {
		(*it).highlight();
	}
}

/**
 * Deactivates highlighting on the display.
 */
void Display::unHighlight() {
	monitor->getProjector()->unHighlight();
	for (std::vector<Projector>::iterator it = projectorList->begin(); it != projectorList->end(); it++)
	{
	 (*it).unHighlight();
	}
}
