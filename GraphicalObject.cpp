#include <glload/gl_3_3.h>
#include <GL/freeglut.h>

#include "GraphicalObject.h"

GraphicalObject::GraphicalObject()
{
}

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

void GraphicalObject::draw()
{
  glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);

  glEnableVertexAttribArray(0);			
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);	
  glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject2);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

  glDrawArrays(GL_TRIANGLES, 0, 3);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

void GraphicalObject::bindBufferData()
{

  glGenBuffers(1, &positionBufferObject);
  glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
  glBufferData(GL_ARRAY_BUFFER, getTrianglesSize(), getTriangles(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);	

  glGenBuffers(1, &positionBufferObject2);
  glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject2);
  glBufferData(GL_ARRAY_BUFFER, getColorsSize(), getColors(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  
}

