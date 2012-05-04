/*
 * View.h
 *
 *  Created on: 25 apr 2012
 *      Author: Helena
 */

#ifndef VIEW_H_
#define VIEW_H_
#include "Scene.h";
#include "Display.h";
#include "Shared.h"

class View
{
	public:
		View();
		View(Display display);
		void setProjectorsRedFactor(int rFactor);
		void highlightBackground(bool h);
		Projector * getProjector(int index);
		Display * getDisplay();
		void toggleGrid(bool g);
		void setDisplay(Display display);
		void updateView(Scene s);
	private:
		bool highlightBackground;
		bool showGrid;
		Display * display;
};
#endif /* VIEW_H_ */
