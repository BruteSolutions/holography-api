#include "View.h";
/*
 * Metoder startade. Vissa saknar implementering då jag inte hittar
 * lämpliga metoder för det i Display.
 *
 * Är ej heller grafisk på något sätt. Behöver mergas med påbörjad grafisk variant. (GTK)
 *
 * Bör inte View ha en referens till Controller då det grafiska måste
 * kunna uppdatera Controller?
 */
View::View(){
	this = new View(NULL);
}

View::View(Display display){
	highlightBackground=false;
	showGrid=false;
	this.display=display;
}

/*
 * Sets all projectors red factor. This
 * method should update Scene when it is changed.
 */
void View::setProjectorsRedFactor(int rFactor, int gFactor, int bFactor){
	// decide whether to throw error or set to limits
	if(rFactor > 255) rFactor = 255;
	if(gFactor > 255) gFactor = 255;
	if(bFactor > 255) bFactor = 255;
	if(rFactor < 0) rFactor = 0;
	if(gFactor < 0) gFactor = 0;
	if(bFactor < 0) bFactor = 0;
	Vec3 factor = { (float) rFactor/255, (float) gFactor/255, (float) bFactor/255)}; 
	display->getColorTranslator().setConversionFactor(factor);
}

/*
 * Highlights background if h is true, if h is false it is
 * turned off. This method should update Scene when it is changed.
 */
void View::highlightBackground(bool h){
	if(h && (!highlightBackground)){
		display->highlight();
		highlightBackground=true;
	}
	if(!h && highlightBackground){
		display->unHighlight();
		highlightBackground=false;
	}
}

/*
 * Returns the specified projector. Is useful if only
 * one projector’s colour balancing needs to be adjusted.
 */
Projector * View::getProjector(int index){
	return display->getProjectors().at(index);
}

/*
 * Returns the Display used
 */
Display * View::getDisplay(){
	return display;
}

/*
 * A grid is projected by the projectors if g is true instead of a
 * possible 3D world. If g is false a possible 3D world is shown.
 */
void View::toggleGrid(bool g = !showgrid){ /*default value parameter */
	showgrid=g;
	//TODO, method in Display that sets a grid
}

/*
 * Sets the display to the display used as input.
 */
void View::setDisplay(Display * display){
	this->display=display;
}

/*
 * Updates the View by render
 */
void View::updateView(Scene s){
	display->display(s);
}