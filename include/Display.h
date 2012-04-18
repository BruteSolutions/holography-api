/*
 * Display.h
 *
 *  Created on: Feb 22, 2012
 *      Author: fericss
 */
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include <vector>
#include "ColorTranslator.h"
#include "Scene.h"
#include "Monitor.h"
#include "Projector.h"

#ifndef DISPLAY_H_
#define DISPLAY_H_
class Display
{
	public:
		Display();
		void display(Scene scn);
		std::vector<Projector>* getProjectors();
		Monitor* getMonitor();
		ColorTranslator* getColorTranslator();
		void addProjector(Projector *p);
		double getBoundingCube();
		void highlight();
		void unHighlight();
		//void setConfigurations(UniversalConfiguration uc);
		//UniversalConfiguration getConfigurations();
	private:
		Monitor *monitor;
		std::vector<Projector> *projectorList;
		ColorTranslator *colorTranslator;
		int numProjectors;
		//final int WIDTH:
		//final int HEIGHT:

};
#endif /* DISPLAY_H_ */
