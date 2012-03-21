#include <vector>
#include <iostream>

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
		
		void translate(Vec3 trans);

	private:
		GLuint positionBufferObject;
		GLuint positionBufferObject2;
		GLuint positionBufferObject3;
		int trianglesSize, colorsSize;
		float *triangles, *colors;
		//4*4 Matrix
		float *transMatrix;
		
};
