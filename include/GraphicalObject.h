#include <vector>
#include <iostream>
#include "Shared.h"
#include "Shader.h"

class GraphicalObject
{
	public:
		GraphicalObject();
		GraphicalObject(float triangle[], int size);
		GraphicalObject(float triangle[], int trianglesSize, float color[], int colorsSize);
		float* getTriangles();
		float* getColors();
		int getTrianglesSize();
		int getColorsSize();
		float getFirstTri();
		void bindBufferData();
		void draw();
    void applyTransformation(GLuint shader);
		
		void translate(Vec3 trans);

	private:
		GLuint positionBufferObject;
		GLuint positionBufferObject2;
		GLuint positionBufferObject3;
		int trianglesSize, colorsSize;
		float *triangles, *colors;
    	Vec3 pos;
};
