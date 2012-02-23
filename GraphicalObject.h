#include <vector>

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
		GLuint positionBufferObject;
	private:
		int trianglesSize, colorsSize;
		float *triangles[];
		float *colors[];
		float *offset[];
		
};
