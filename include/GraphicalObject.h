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
	
		void setOrigin(Vec3 ori);	void rotate();
    void applyTransformation(GLuint shader);
	void applyRotation(GLuint shader);
//	void rotate(Vec3 trans);
		
		void resize(double factor);
		void setScale(double _scale);
		double getScale();
		void incrementScale(double inc);
		void translate(Vec3 trans);
		Vec3 origin; 
		
		bool hasMesh();
		void setMesh(bool mesh);

	float angleX, angleY, angleZ;
	private:
		GLuint positionBufferObject;
		GLuint positionBufferObject2;
		GLuint positionBufferObject3;
		int vertexDataSize, colorDataSize;
		float *vertexData, *colorData;
    	Vec3 pos;
		Mat4 objectRotX,objectRotY,objectRotZ;
		bool mesh;
		float scale;

};
#endif
