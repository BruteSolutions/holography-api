/*
 * Controller.cpp
 *
 *  Created on: 3 may 2012
 *      Author: Helena
 *
 *  A sceleton mainly. How to solve the user interface? Should it be a
 *  part of View? If so, View has
 *
 *  There is also methods involving user input that needs
 *  to be built and also methods that cannot be
 *  implemented at the moment because of lack of
 *  funcionality in other classes.
 */

#include "Controller.h"

/*
 *
 */
Controller::Controller(Model model, View view) {
  Controller::model = model;
	Controller::view = view;
	Controller::showGrid=false;
	Controller::showMesh=false;
	Controller::state=0;
	Controller::backgroundHighlightning=false;
	//TODO: More actions probably requiered
}

bool Controller::backgroundHighlightning() {
	return backgroundHighlightning;
}

void Controller::highlightBackground() {
	if (!backgroundHighlightning) {
		backgroundHighlightning = true;
		view.display.highlight();
	}
}

void Controller::highlightBackground(bool highlight) {
	if (backgroundHighlightning!=highlight) {
		backgroundHighlightning = highlight;
		if(highlight){
			highlightBackground();
		}
		else{
			unHighlightBackground();
		}
	}
}

void Controller::unHighlightBackground() {
	if (backgroundHighlightning) {
		backgroundHighlightning = false;
		view.display.unHighlight();
	}
}

//void Controller::MouseListener(MouseEvent me){
//TODO
//}

//void Controller::KeyboardListener(KeyboardEvent ke){
//TODO
//}

Model * Controller::getModel() {
	return model;
}

/*
 * states:
 * 0 - null state
 * 1 - rotateWorld
 * 2 - translateWorld
 */
int Controller::getState() {
	//TODO: Decisions need to be taken about what states and how to handle them
	return state;
}

View * Controller::getView() {
	return view;
}

void Controller::rotateWorld(){
	Controller::state=1;
	//TODO: Rotate world action
	//Should be done through scene.threeDSpace.GraphicalObject but cannot find it.
}

GraphicalObject * Controller::selectedObject() {
	return Controller::selectedObject;
}

bool Controller::showMesh() {
	return Controller::showMesh;
}

bool Controller::showGrid() {
	return Controller::showGrid;
}

void Controller::translateWorld(){
	state=2;
	//TODO
	//translate is positioned in GraphicalObject, which is in threeDSpace, which is in scene.
}
