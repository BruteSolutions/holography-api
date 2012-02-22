#include <iostream>
#include "GraphicalObject.cpp"
 
float vertexPositions[] = {
	0.60f, 0.5f, 0.0f, 1.0f,
	0.75f, -0.75f, 0.0f, 1.0f,
	-0.50f, -0.75f, 0.0f, 1.0f,
};

int main ()
{
	//Nytt grafiskt obj från vertexPositions
	GraphicalObject * ac = new GraphicalObject(vertexPositions);	
	
  	std::cout << "Hello, world! " << ac->getFirstTri() <<" första float\n";

	//Ändringar på vertexposition ändrar också triangles
	vertexPositions[0]=23.2f;
	std::cout << ac->getFirstTri() <<" Ändrad\n";

	//Hämta poineter till tringles
	float * a= ac->getTriangles();
	std::cout << a[1] <<"\n";

	//Pointern kan också änrda på triangles;
	a[1] = 4.3f;
	std::cout << a[1] <<"\n";

  	return 0;
}
