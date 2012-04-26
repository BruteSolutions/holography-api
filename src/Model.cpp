#include "Model.h"
#include "ThreeDSpace.h"


/**
 * Constructor for Model
 */
Model::Model(){
	//Should this one do anything?
}

/*
 * Constructor for Model setting scene to the scene used as input
 */
Model::Model(Scene scene){
	this.scene=scene;
}

/*
 * Adds an object to the 3D World
 */
void View::addGraphicalObject(GraphicalObject object){
	//TODO
}

/*
 * Sets the cursor’s colour
 */
void View::setCursorsColor(int r, int g, int b){
	//TODO
	//Cannot be done at the moment as we are missing a cursor
}

/*
 * Returns the cursors position in the 3D world.
 */
Vec3 View::getCursorsPosition(){
	//TODO
	//Cursor saknas så går ej att göra
	return null;
}

/*
 * Sets the cursor’s position. This and the
 * above method are useful when the cursor’s position shall be updated.
 */
void View::setCursorsPosition(Vec3 position){
	//TODO
	//Cursos saknas så går ej att implementera
}

/*
 * Returns the camera’s position in the 3D world
 */
Vec3 View::getCameraPosition(){
	//TODO
	return null;
}

/*
 * Sets the camera’s position.
 */
void View::setCamerasPosition(Vec3 position){
	//TODO
}

/*
 * Return the camera’s direction of sight.
 */
Vec3 View::getCamerasDirectionOfSight(){
	//TODO
	return null;
}

/*
 * Sets the camera’s direction of sight.
 */
void View::setCamerasDirectionOfSight(Vec3 direction){
	//TODO
}


/*
 * Returns the Scene. Must be provided when View wants it in order to
 * update some visual settings that the user has changed (like highlighting the background).
 */
Scene View::getScene(){
	return scene;
}

/*
 * Rescales the world according to the camera screen’s size.
 */
void View::rescale(){
	//TODO
}
