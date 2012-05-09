/*
 * Model.h
 *
 *  Created on: 25 apr 2012
 *      Author: Helena
 *      
 * 	Edited 2012-05-03
 *
 *      Should there be a cursor?
 */

#ifndef MODEL_H_
#define MODEL_H_
#include "Scene.h";
#include "GraphicalObject.h"
#include "Shared.h"

class Model
{
	public:
		Model();
		Model(Scene scene);
		GraphicalObject getFirstObjectInDirection(Vec3 direction, Vec3 origin);
		void resize(double factor);
		void addGraphicalObject(GraphicalObject object);
		void setCursorsColor(int r, int g, int b);
		Vec3 getCursorsPosition();
		void highlightBackground(bool highlight);
		void setCursorsPosition(Vec3 position);
		Vec3 getCameraPosition();
		void setCamerasPosition(Vec3 position);
		Vec3 getCamerasDirectionOfSight();
		void setCamerasDirectionOfSight(Vec3 direction);
		Scene * getScene();
		void rescale();
	private:
		Scene * scene;
		//Cursor? Class and header cannot be found?
};

#endif /* MODEL_H_ */
