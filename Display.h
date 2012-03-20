/*
 * Display.h
 *
 *  Created on: Feb 22, 2012
 *      Author: fericss
 */


#ifndef DISPLAY_H_
#define DISPLAY_H_
#include "Projector.h"
#include "ColorTranslator.h"
#include "Scene.h"
#include "Monitor.h"
//#include "Projector.h"
class Display
{
	public:
	Display();
	void highlight();
	void unHighlight();
	double getBoundingCube();
	Projector** getProjectors();
	void display(Scene scn);
	Monitor* getMonitor();
	ColorTranslator* getColorTranslator();

	private:
	ColorTranslator myColorTrans;
	Projector *projectorList[10];
	Monitor myMonitor;
	int numProjectors;

};
#endif /* DISPLAY_H_ */
