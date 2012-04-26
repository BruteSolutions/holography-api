#include "View.h";
/*
 * Metoder startade. Vissa saknar implementering då jag inte hittar
 * lämpliga metoder för det i Display.
 *
 * Är ej heller grafisk på något sätt. Behöver mergas med påbörjad grafisk variant.
 *
 * Bör inte View ha en referens till Controller då det grafiska måste
 * kunna uppdatera Controller?
 */
View::View(){
	View::View(null);
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
void View::setProjectorsRedFactor(int rFactor){
	//TODO
	//Don't know how to do this
}

/*
 * Highlights background if h is true, if h is false it is
 * turned off. This method should update Scene when it is changed.
 */
void View::highlightBackground(bool h){
	if(h && (!highlightBackground)){
		display.highlight();
		highlightBackground=true;
	}
	if(!h && highlightBackground){
		display.unHighlight();
		highlightBackground=false;
	}
}

/*
 * Returns the specified projector. Is useful if only
 * one projector’s colour balancing needs to be adjusted.
 */
Projector View::getProjector(int index){
	//TODO
	//Don't know how to do this. Can't find any methods for it
	return null;
}

/*
 * Returns the Display used
 */
Display View::getDisplay(){
	return Display;
}

/*
 * A grid is projected by the projectors if g is true instead of a
 * possible 3D world. If g is false a possible 3D world is shown.
 */
void View::toggleGrid(bool g){
	showgrid=g;
	//Don't know how to do this. Can't find any methods for it
	//TODO
}

/*
 * Sets the display to the display used as input.
 */
void View::setDisplay(Display display){
	this.display=display;
}

/*
 * Updates the View by render
 */
void View::updateView(Scene s){
	//TODO
	//Don't know how to do this. Can't find any methods for it
}
