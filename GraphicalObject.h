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
		void draw2()
		{
			glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
			glEnableVertexAttribArray(0);			
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);	
	

			glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject2);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);			
			glEnableVertexAttribArray(1);

			glDrawArrays(GL_TRIANGLES, 0, 3);

			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
		}

		void bindBufferData2()
		{
			glGenBuffers(1, &positionBufferObject);
			glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
			glBufferData(GL_ARRAY_BUFFER, getTrianglesSize(), getTriangles(), GL_STATIC_DRAW);

			glGenBuffers(1, &positionBufferObject2);
			glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject2);
			glBufferData(GL_ARRAY_BUFFER, getColorsSize(), getColors(), GL_STATIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, 0);	
			
		}
		GLuint positionBufferObject;
		GLuint positionBufferObject2;

	private:
		int trianglesSize, colorsSize;
		float *triangles, *colors;
		float *offset;
		
		
};
