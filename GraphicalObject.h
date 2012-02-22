#include <vector>

class GraphicalObject
{
	public:
		GraphicalObject();
		GraphicalObject(float triangle[]);
		GraphicalObject(float triangle[], float color[]);
		float* getTriangles();
		float* getColors();

		float getFirstTri();
	private:
		float *triangles[];
		float *colors[];
		float *offset[];		
};
