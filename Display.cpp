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

Display::Display(){

    // Hardcoded color
    float flo[3] = { 1.0f, 1.0f, 1.0f};
    myColorTrans = ColorTranslator(flo);
    myMonitor = Monitor();

    //TODO
    numProjectors = 4; // Temp
    for(int i = 0; i<numProjectors; i++){
	//TODO This does not work at all, just placed there because it can compile
   	 projectorList[i] = new Projector(&numProjectors,2049);
    }
}

/* Displays the 3D space given on the regular monitor as well as the holographic display. */
void Display::display(Scene scn){
    for(int i = 0; i<numProjectors; i++){
	projectorList[i]->display(scn);
    }
    myMonitor.display(scn);
}

/* Returns an array of the projector objects associated with the holographic display. */
Projector** Display::getProjectors(){
    return projectorList;
}

/* Returns the Monitor object associated with the computer’s ordinary display. */
Monitor* Display::getMonitor(){
    return &myMonitor;
}

/* Returns the component used by the Display object to impose default colour settings on each projector. */
ColorTranslator* Display::getColorTranslator(){
    return &myColorTrans;
}

double Display::getBoundingCube(){
	//todo
}

/* Brightens the background of the holographic display. If the background is already highlighted, nothing will change. */
void Display::highlight(){
    for(int i = 0; i<numProjectors;i++){
        projectorList[i]->highlight();
    }
}

/* Darkens the background of the holographic display. If the background is not highlighted, nothing will change. */
void Display::unHighlight(){
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


