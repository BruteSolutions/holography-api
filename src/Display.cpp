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
 * Constructs a new Display object and initiates the associated Monitor and
 * ColorTranslator object.
 */
Display::Display() {
    monitor = new Monitor();
    projectorList = new std::vector<Projector>();

    //COLORTRANSLATOR??
    colorTranslator = new ColorTranslator();
}

/**
 * Displays the given scene on the associated monitor and projectors.
 * @param scene the Scene object to display.
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
 * Returns all the associated projectors.
 * @return an std::vector containing all the associated Projector objects.
 */
std::vector<Projector>* Display::getProjectors(){
    return projectorList;
}

/**
 * Adds a projector to the display.
 * @param projector a Projector object to be added.
 */
void Display::addProjector(Projector *projector){
    if(projector != NULL){
        projectorList->push_back(*projector);
    }
}

/**
 * Returns the associated monitor.
 * @return the associated Monitor object.
 */
Monitor* Display::getMonitor() {
    return monitor;
}

/**
 * Returns the associated color translator.
 * @return the associated ColorTranslator object.
 */
ColorTranslator* Display::getColorTranslator() {
    return colorTranslator;
}

/**
 * Returns the current bounding cube.
 * @return a double representing the bounding cube.
 */
double Display::getBoundingCube() {
    //todo
}

/**
 * Highlights the display, that is making it shine brighter than normal.
 */
void Display::highlight(){
    monitor->getProjector()->highlight();
    for (std::vector<Projector>::iterator it = projectorList->begin(); it != projectorList->end(); it++) {
        (*it).highlight();
    }
}

/**
 * Deactivates highlighting on the display.
 * @see highlight()
 */
void Display::unHighlight() {
    monitor->getProjector()->unHighlight();
    for (std::vector<Projector>::iterator it = projectorList->begin(); it != projectorList->end(); it++)
    {
     (*it).unHighlight();
    }
}

/**
 * Sets the configuration for the projectors.
 * @param uc the UniversalConfiguration to be used by the associated projectors.
 */
void Display::setConfigurations(UniversalConfiguration uc){
    colorTranslator = uc.getColorTranslator();
    configs = uc.getProjectorConfigurations();
    int min = configs->size() < projectorList->size() ? configs->size() : projectorList->size();
    for (int i = 0; i<min; i++) {
        (projectorList->at(i)).setConfiguration(configs->at(i));
    }    
}

/**
 * Returns the configuration for the projectors.
 * @return a new UniversalConfiguration containing the configurations for the
 * associated projectors.
 */
UniversalConfiguration * Display::getConfigurations(){
    configs = new std::vector<Configuration>();
    for (std::vector<Projector>::iterator it = projectorList->begin(); it != projectorList->end(); it++) {
        configs->push_back(it->getConfiguration());
    }
    return (new UniversalConfiguration(configs, colorTranslator));
}
