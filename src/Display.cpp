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

Display::Display(){
	myMonitor = new Monitor();

	// in i config fil och hämta antal projektorer
	//TODO
//	numProjectors = 4; // Temp
//	projectorList = new std::vector<Projector>();
//	for(int i = 0; i<numProjectors; i++){
		//TODO buffer of size len at memory (inte 50)
//		projectorList->push_back(Projector(NULL, 0));
//	}
	myColorTrans = new ColorTranslator();
}
void Display::display(Scene scn){
//	myColorTrans->apply();
for(int i = 0; i<numProjectors; i++){
 (projectorList->at(i)).display(scn);
}
myMonitor->display(scn);
	//todo göra klart
}
std::vector<Projector>* Display::getProjectors(){
	return projectorList;
}
void Display::addProjector(Projector p){
	projectorList->push_back(p);
}
Monitor* Display::getMonitor(){
	return myMonitor;
}
ColorTranslator* Display::getColorTranslator(){
	return myColorTrans;
}
double Display::getBoundingCube(){
	//todo
}
void Display::highlight(){
	//todo
	//	for each(Projector p in projector):
	//	       p.highlight();
	for(int i = 0; i<numProjectors;i++){
		(projectorList->at(i)).highlight();
	}
}
void Display::unHighlight(){
	//todo
	for(int i = 0; i<numProjectors;i++){
		(projectorList->at(i)).unHighlight();
	}
}
//void Display::setConfigurations(UniversalConfiguration uc){
		//todo
//}
//UniversalConfiguration Display::getConfigurations(){
	//todo
//}

