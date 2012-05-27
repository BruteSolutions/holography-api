#ifndef __GRAPHICALOBJECT_H
#define __GRAPHICALOBJECT_H
#include <vector>
#include <iostream>
#include "Shared.h"
#include "Shader.h"

class GraphicalObject {
public:
	GraphicalObject();
	GraphicalObject(float vertexData[], int size);
	GraphicalObject(float vertexData[], int vertexDatasSize, float colorData[], int ColorDataSize);
	float* getVertexData();
	float* getColorData();
	int getVertexDataSize();
	int getColorDataSize();
	void bindBufferData();
	void draw();
	void setOrigin(Vec3 ori);
	Vec3 getOrigin();
	void setColorTriangle(int index, Vec3Int color);	
	void rotate();
	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);
	void rotateXRad(float angle);
	void rotateYRad(float angle);
	void rotateZRad(float angle);
	void applyTransformation(GLuint shader);
	void applyRotation(GLuint shader);
//	void rotate(Vec3 trans);	
	void resize(double factor);
	void setHighlightUniform(GLuint shader);
	void toggleHighlight();
	void setHighlight(bool _bool);
	void setScale(double _scale);
	double getScale();
	void incrementScale(double inc);
	void translate(Vec3 trans);
	Vec3 origin; 	
	bool hasMesh();
	bool highlighted();
	void setMesh(bool mesh);
	void setPosition(Vec3 pos);
	Vec3 getPosition();
	void center(Vec3 camPos, Vec3 optPos);
	//When following floats are private: the first triangle is permanently meshed. WHY?=
	float angleX, angleY, angleZ;
	
private:
	GLuint positionBufferObject;
	GLuint positionBufferObject2;
	GLuint positionBufferObject3;
	bool highlight;
	int vertexDataSize, colorDataSize;
	float *vertexData, *colorData;
	Vec3 pos;
	Mat4 rotationMatrix;
	Mat4 objectRotX,objectRotY,objectRotZ;
	bool mesh;
	float scale;
	

};
#endif
