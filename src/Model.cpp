#include "Model.h"
#include "ThreeDSpace.h"


/**
 * Constructor for Model
 *
 * Edited: 2012-05-03
 */
Model::Model(){
	//Should this one do anything?
}

/*
 * Constructor for Model setting scene to the scene used as input
 */
Model::Model(Scene scene){
	Model::scene=scene;
}

/*
 * Adds an object to the 3D World
 */
void Model::addGraphicalObject(GraphicalObject * object){
	ThreeDSpace * threeD=Model::scene.get3DSpace();
	threeD->addObject(object);
}

/*
 * Sets the cursor’s colour
 */
void Model::setCursorsColor(int r, int g, int b){
	//TODO
	//Cannot be done at the moment as we are missing a cursor
}

/*
 * Returns the cursors position in the 3D world.
 */
Vec3 Model::getCursorsPosition(){
	//TODO
	//Cursor saknas så går ej att göra
	return null;
}

/*
 * Sets the cursor’s position. This and the
 * above method are useful when the cursor’s position shall be updated.
 */
void Model::setCursorsPosition(Vec3 position){
	//TODO
	//Cursor saknas så går ej att implementera
}

/*
 * Returns the camera’s position in the 3D world
 */
Vec3 Model::getCameraPosition(){
	return Model::scene.getCameraPosition();
}

/*
 * Sets the camera’s position.
 */
void Model::setCamerasPosition(Vec3 position){
	Model::scene->cPos=position;
	//TODO scene needs to be updated
	// Functionality in Scene is missing
}

/*
 * Return the camera’s direction of sight.
 */
Vec3 Model::getCamerasDirectionOfSight(){
	return Model::scene->cDir;
}

void Model::highlightBackground(bool highlight){
	//TODO: Highlight background by accessing scene, which doesn't seem to be possible at the moment.
}

/*
 * Sets the camera’s direction of sight.
 */
void Model::setCamerasDirectionOfSight(Vec3 direction){
	Model::scene->cDir=direction;
	//TODO Funcionality is missing in Scene
	//	Model::scene.????(direction) There should be a method here for this!
}


/*
 * Returns the Scene. Must be provided when View wants it in order to
 * update some visual settings that the user has changed (like highlighting the background).
 */
Scene Model::getScene(){
	return Model::scene;
}

/*
 * Rescales the world according to the camera screen’s size.
 */
void Model::rescale(){
	//TODO Cannot find functionality
}
