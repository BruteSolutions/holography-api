#include "GraphicalObject.h"

GraphicalObject::GraphicalObject()
{
}

GraphicalObject::GraphicalObject(float triangle[])
{
	*triangles = triangle;
}

GraphicalObject::GraphicalObject(float triangle[], float color[])
{
	*triangles = triangle;
	*colors = color;
}

float GraphicalObject::getFirstTri()
{
	return *triangles[0];
}

float* GraphicalObject::getTriangles()
{	
	return *triangles;
}

float* GraphicalObject::getColors()
{	
	return *colors;
}

