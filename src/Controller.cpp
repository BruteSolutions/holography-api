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

//De här finns redan i openGl om ni kollar i test-economy men de fungerar bara på själva fönstren
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

void Controller::rotateObject(Vec3 rotationAngles){
	//State bs?
	
	selectedObject->rotateX(rotationAngles.x);
	selectedObject->rotateY(rotationAngles.y);
	selectedObject->rotateZ(rotationAngles.z);
}

void Controller::rotateWorld(Vec3 rotationAngles){
	Controller::state=1;
	
	model->getScene()->rotateX(rotationAngles.x);
	model->getScene()->rotateY(rotationAngles.y);
	model->getScene()->rotateZ(rotationAngles.z);
	
	//TODO: Rotate world action
	//Should be done through scene.threeDSpace.GraphicalObject but cannot find it.
}

GraphicalObject * Controller::selectedObject() {
	return selectedObject;
}

GraphicalObject * Controller::selectedNextObject() {
	model->getScene()->selectNext();	
	selectedObject = model->getScene()->getSelected().at(0);
	return selectedObject;
}

bool Controller::showMesh() {	
	selectedObject->setMesh(true);
	return true;
}

bool Controller::toggleMesh() {	
	selectedObject->setMesh(!selectedObject.hasMesh());
	return selectedObject->hasMesh();
}

bool Controller::showGrid() {
	return showGrid;
}

void Controller::translateWorld(Vec3 translation){
	state=2;
	//TODO
	//translate is positioned in GraphicalObject, which is in threeDSpace, which is in scene.
	/*
	When Scene is updated.
	model->getScene()->translate(translation);
	*/
	//TEMP
	model->getScene()->cPos.x += translation.x;
	model->getScene()->cPos.y += translation.y;
	model->getScene()->cPos.z += translation.z;
}
