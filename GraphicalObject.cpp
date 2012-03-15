#include "glload/include/glload/gl_3_3.h"
#include <GL/freeglut.h>

#include "GraphicalObject.h"

GraphicalObject::GraphicalObject()
{
}

//GraphicalObject::GraphicalObject(float triangle[], int _trianglesSize)
//{
//	*triangles = triangle;
//	trianglesSize = _trianglesSize;
//}

GraphicalObject::GraphicalObject(float _triangles[], int _trianglesSize, float _colors[], int _colorsSize)
{	
	triangles = _triangles;
	colors = _colors;	
	
	trianglesSize = _trianglesSize;
	colorsSize = _colorsSize;
}

float GraphicalObject::getFirstTri()
{
	return triangles[0];
}

float* GraphicalObject::getTriangles()
{	
	return triangles;
}

float* GraphicalObject::getColors()
{	
	return colors;
}

int GraphicalObject::getTrianglesSize()
{	
	return trianglesSize;
}

int GraphicalObject::getColorsSize()
{	
	return colorsSize;
}

void GraphicalObject::bindBufferData()
{
	glGenBuffers(1, &positionBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glBufferData(GL_ARRAY_BUFFER, getTrianglesSize(), getTriangles(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void GraphicalObject::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, sizeof(float), GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
}


