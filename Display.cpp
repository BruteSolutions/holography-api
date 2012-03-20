//============================================================================
// Name        : Display.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include "Display.h"
using namespace std;
#include "Monitor.h"
#include "ColorTranslator.h"

int main(void) {
	Display();
	return 0;
}
int numProjectors;


Display::Display(){;


	// Hårdkodad color
	float flo[3] = { 1.0f, 1.0f, 1.0f};
	myColorTrans = ColorTranslator(flo);
	myMonitor = Monitor();

	// in i config fil och hämta antal projektorer
	//TODO
	numProjectors = 4; // Temp
	for(int i = 0; i<numProjectors; i++){
		//TODO This does not work at all, just placed there because it can compile
		projectorList[i] = new Projector(&numProjectors,2049);
	}


}

void Display::display(Scene scn){
	//myColorTrans->apply();
	//todo göra klart
//	apply colorTranslator
//	for each(Projector p in projector):
//		p.display(scn);
//	m.display(scn);
//

	for(int i = 0; i<numProjectors; i++){
		projectorList[i]->display(scn);
	}
	myMonitor.display(scn);
}

Projector** Display::getProjectors(){
	return projectorList;
}

Monitor* Display::getMonitor(){
	return &myMonitor;
}


ColorTranslator* Display::getColorTranslator(){
	return &myColorTrans;
}

double Display::getBoundingCube(){
	//todo
}
void Display::highlight(){
	//todo
	//	for each(Projector p in projector):
	//	       p.highlight();
	for(int i = 0; i<numProjectors;i++){
		projectorList[i]->highlight();
	}
}
void Display::unHighlight(){
	//todo
	for(int i = 0; i<numProjectors;i++){
		projectorList[i]->unHighlight();
	}
}
//void setConfigurations(UniversalConfiguration uc){
//	//todo
//
//}
//UniversalConfiguration getConfigurations(){
//	//todo
//}


