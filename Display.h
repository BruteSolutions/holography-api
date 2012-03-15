/*
 * Display.h
 *
 *  Created on: Feb 22, 2012
 *      Author: fericss
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_
class Display
{
	public:
		void Display();
		void display(Scene scn);
		int getProjectors();
		Monitor getMonitor();
		ColorTranslator getColorTranslator();
		double getBoundingCube();
		void highlight();
		void unHighlight();
		void setConfigurations(UniversalConfiguration uc);
		UniversalConfiguration getConfigurations();
	private:
		Monitor myMonitor;
		Projector projectorList;
		ColorTranslator myColorTrans;
		int numProjectors;
		//final int WIDTH:
		//final int HEIGHT:

}
#endif /* DISPLAY_H_ */
