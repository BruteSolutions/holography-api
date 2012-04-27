#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include <cstring>
#include "Shared.h"
#include "GraphicalObject.h"
#include <stdio.h>
#include <math.h>

GraphicalObject::GraphicalObject()
{
}

GraphicalObject::GraphicalObject(float _vertexData[], int _vertexDataSize, float _colorData[], int _colorDataSize)
{	
	vertexData = _vertexData;
	colorData = _colorData;	
	
	vertexDataSize = _vertexDataSize;
	colorDataSize = _colorDataSize;
	memset(&pos, 0, 4*3);
	memset(&objectRotX.m, 0, sizeof(objectRotX.m));
	memset(&objectRotY.m, 0, sizeof(objectRotY.m));
	memset(&objectRotZ.m, 0, sizeof(objectRotZ.m));
	objectRotX.m[0]=1;
	objectRotX.m[5]=-1;
	objectRotX.m[10]=1;
	objectRotX.m[15]=1;	

	objectRotY.m[0]=1;
	objectRotY.m[5]=1;
	objectRotY.m[10]=1;
	objectRotY.m[15]=1;

	objectRotZ.m[0]=1;
	objectRotZ.m[5]=1;
	objectRotZ.m[10]=1;
	objectRotZ.m[15]=1;
	scale = 1;
	angleX = 0;
	angleY = 0;
	angleZ = 0;
}

float GraphicalObject::getFirstTri()
{
	return vertexData[0];
}

float* GraphicalObject::getVertexData()
{	
	return vertexData;
}

float* GraphicalObject::getColorData()
{	
	return colorData;
}

int GraphicalObject::getVertexDataSize()
{	
	return vertexDataSize;
}

int GraphicalObject::getColorDataSize()
{	
	return colorDataSize;
}

void GraphicalObject::draw()
{





  glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);

  glEnableVertexAttribArray(0);			
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);	
  glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject2);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

  glDrawArrays(                   GL_TRIANGLES, 0, getVertexDataSize()/4);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

void GraphicalObject::bindBufferData()
{

  glGenBuffers(1, &positionBufferObject);
  glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
  glBufferData(GL_ARRAY_BUFFER, getVertexDataSize()*4, getVertexData(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);	

  glGenBuffers(1, &positionBufferObject2);
  glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject2);
  glBufferData(GL_ARRAY_BUFFER, getColorDataSize()*4, getColorData(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glFlush();
}
void GraphicalObject::rotate(){

	objectRotX.m[5] = cos(angleX);
	objectRotX.m[6] = -sin(angleX);
	objectRotX.m[9] = sin(angleX);
	objectRotX.m[10] = cos(angleX); 

	objectRotY.m[0] = cos(angleY);
	objectRotY.m[2] = sin(angleY);
	objectRotY.m[8] = -sin(angleY);
	objectRotY.m[10] = cos(angleY); 

	objectRotZ.m[0] = cos(angleZ);
	objectRotZ.m[1] = -sin(angleZ);
	objectRotZ.m[4] = sin(angleZ);
	objectRotZ.m[5] = cos(angleZ); 

}
void GraphicalObject::applyRotation(GLuint shader){
/*	for(int i = 0; i < 16; i++){
		printf("%f ",objectRotX.m[i]);
	}
	printf("\n");
for(int i = 0; i < 16; i++){
		printf("%f ",objectRotY.m[i]);
	}
	printf("\n");
for(int i = 0; i < 16; i++){
		printf("%f ",objectRotZ.m[i]);
	}
	printf("\n");*/
//skapa en metod som sätter alla uniforms istället
	GLuint scaleLoc = glGetUniformLocation(shader, "scale");
	glUniform1f(scaleLoc, scale);

	GLuint originLoc = glGetUniformLocation(shader, "objOrigin");
	glUniform3f(originLoc, origin.x,origin.y,origin.z);


	//std::cout << "\n\n"<<scale<<"\n\n";
	GLuint posLocX = glGetUniformLocation(shader, "objectRotX");
    glUniformMatrix4fv(posLocX , 1, GL_FALSE, objectRotX.m);
	
	GLuint posLocY = glGetUniformLocation(shader, "objectRotY");
    glUniformMatrix4fv(posLocY , 1, GL_FALSE, objectRotY.m);

	GLuint posLocZ = glGetUniformLocation(shader, "objectRotZ");
    glUniformMatrix4fv(posLocZ , 1, GL_FALSE, objectRotZ.m);
}

void GraphicalObject::translate(Vec3 trans)
{
  Vec3 newPos = {pos.x+trans.x, pos.y+trans.y, pos.z+trans.z};
  pos = newPos;
}

void GraphicalObject::applyTransformation(GLuint shader)
{
    GLuint posLoc = glGetUniformLocation(shader, "objectPos");
    glUniform3f(posLoc, pos.x, pos.y, pos.z);
}

void GraphicalObject::setOrigin(Vec3 ori)
{
	origin = ori;
}

