/*
 * Controller.h
 *
 *  Edited on: 3 may 2012
 *      Author: Helena
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include "GraphicalObject.h"
#include "View.h"
#include "Model.h"
#include "Shared.h"

class Controller
{
	public:
		Controller(Model model, View view);
//		void MouseListener(MouseEvent me); Needs to get something imported
//		void KeyboardListener(KeyboardEvent ke);
		bool backgroundHighlightning();
		Model * getModel();
		int getState();
		View * getView();
		void highlightBackground();
		void highlightBackground(bool highlight)
		void unHighlightBackground();
		void rotateWorld(Vec3 r);
		void rotateObject(Vec3 rotationAngles);
		GraphicalObject * selectedObject();
		GraphicalObject * selectedNextObject();
		bool showMesh();
		bool showGrid();
		void translateWorld(Vec3 t);
	private:
		int state;
		bool backgroundHighlightning;
		bool showGrid;
		bool showMesh;
		GraphicalObject * selectedObject;
		View * view;
		Model * model;
};


#endif /* CONTROLLER_H_ */
