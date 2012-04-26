/*
 * Controller.h
 *
 *  Created on: 25 apr 2012
 *      Author: Helena
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include "GraphicalObject.h"
#include "View.h"
#include "Shared.h"

class Controller
{
	public:
		Controller(Model model, View view);
		bool backgroundHighlightning();
		Model getModel();
		int getState();
		View getView();
		GraphicalObject selectedObject();
		bool showMesh();
		bool showGrid();
	private:
		int state;
		bool backgroundHighlightning;
		bool showGrid;
		bool showMesh;
		View view;
		Model model;
};


#endif /* CONTROLLER_H_ */
