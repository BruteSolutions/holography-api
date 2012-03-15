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

	private:
		GLuint positionBufferObject;
		GLuint positionBufferObject2;
		int trianglesSize, colorsSize;
		float *triangles, *colors;
		float *offset;
		
		
};
