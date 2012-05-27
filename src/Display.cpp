#include <iostream>
#include <vector>
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include "Display.h"
#include "Scene.h"
#include "Monitor.h"
#include "Projector.h"
#include "UniversalConfiguration.h"

/**
 * Initiates the associated objects.
 */
Display::Display() {
	monitor = new Monitor();
	projectorList = new std::vector<Projector>();

	colorTranslator = new ColorTranslator();
}

/**
 * Update each window with the buffers containing our objects 
 * (has to be called whenever the amount of objects to be drawn are modified
 * or when changing scenes)
 * @param scene The scene to be bound to each window handled in display
 */
void Display::rebindBuffers(Scene *scene) {
	//save the current window
	int currentWindow = glutGetWindow();

	//draw monitor
	glutSetWindow(1); //monitor
	scene->get3DSpace()->bindBuffers();

	//draw projectors
	int windowBuffer = 2;
	for (std::vector<Projector>::iterator it = projectorList->begin(); it != projectorList->end(); it++) {
		glutSetWindow(windowBuffer);
		scene->get3DSpace()->bindBuffers();
		windowBuffer++;
	}
	
	glutSetWindow(currentWindow);
	//change back to the current window

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

/**
 * Set the configuration for the projectors
 * @param UniversalConfiguration uc to set
 */
void Display::setConfigurations(UniversalConfiguration *uc){
	colorTranslator = uc->getColorTranslator();
	configs = uc->getProjectorConfigurations();
	int min = configs->size() < projectorList->size() ? configs->size() : projectorList->size();
	for (int i = 0; i<min; i++) {
		(projectorList->at(i)).setConfiguration(configs->at(i));
	}
	
}

/**
 * Get the configuration from the projectors.
 * @return UnivercalConfiguration
 */
UniversalConfiguration * Display::getConfigurations(){
	configs = new std::vector<Configuration>();
	for (std::vector<Projector>::iterator it = projectorList->begin(); it != projectorList->end(); it++) {
		configs->push_back(it->getConfiguration());
	}
	return (new UniversalConfiguration(configs, colorTranslator));
}
