//============================================================================
// Name        : Display.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include "Display.h"
#include "Scene.h"
#include "Monitor.h"
#include "Projector.h"




//todo

Display::Display() {
	monitor = new Monitor();
	projectorList = new std::vector<Projector>();

	//COLORTRANSLATOR??
	colorTranslator = new ColorTranslator();
}
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

std::vector<Projector>* Display::getProjectors(){
	return projectorList;
}
void Display::addProjector(Projector *projector){
	if(projector != NULL){
		projectorList->push_back(*projector);
	}
}

Monitor* Display::getMonitor() {
	return monitor;
}

ColorTranslator* Display::getColorTranslator() {
	return colorTranslator;
}

double Display::getBoundingCube() {
	//todo
}

void Display::highlight(){
	monitor->getProjector()->highlight();
	for (std::vector<Projector>::iterator it = projectorList->begin(); it != projectorList->end(); it++) {
		(*it).highlight();
	}
}

void Display::unHighlight() {
	monitor->getProjector()->unHighlight();
	for (std::vector<Projector>::iterator it = projectorList->begin(); it != projectorList->end(); it++)
	{
	 (*it).unHighlight();
	}
}

//void Display::setConfigurations(UniversalConfiguration uc){
		//todo
//}
//UniversalConfiguration Display::getConfigurations(){
	//todo
//}

