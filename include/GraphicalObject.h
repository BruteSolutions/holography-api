#ifndef __GRAPHICALOBJECT_H
#define __GRAPHICALOBJECT_H
#include <vector>
#include <iostream>
#include "Shared.h"
#include "Shader.h"

class GraphicalObject
{
	public:
		GraphicalObject();
		GraphicalObject(float vertexData[], int size);
		GraphicalObject(float vertexData[], int vertexDatasSize, float colorData[], int ColorDataSize);
		float* getVertexData();
		float* getColorData();
		int getVertexDataSize();
		int getColorDataSize();
		float getFirstTri();
		void bindBufferData();
		void draw();
		void rotate();
		void setOrigin(Vec3 ori);
    void applyTransformation(GLuint shader);
	void applyRotation(GLuint shader);
//	void rotate(Vec3 trans);
		float scale;
		void translate(Vec3 trans);
		float angleX, angleY, angleZ;
		Vec3 origin; 
	private:
		GLuint positionBufferObject;
		GLuint positionBufferObject2;
		GLuint positionBufferObject3;
		int vertexDataSize, colorDataSize;
		float *vertexData, *colorData;
    	Vec3 pos;
		Mat4 objectRotX,objectRotY,objectRotZ;

};
#endif
