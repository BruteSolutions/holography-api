#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
#include "Shared.h"
#include "Scene.h"
#include "RawLoader.h"

/** 
 * Parses a file and builds a scene containing graphical objects
 * @param path the filepath which to create a scene from
 * @return a Scene containing the objects specified in the file
 */
static Scene* loadFile(std::string path) throw (std::string) {
	std::ifstream rawfile;
	Vec3 pos;
	char nl;
	float * vertexData, * colorData;
	unsigned int numObjects, numTriangles;
	Scene * scene = new Scene();
	
	/* open the file */
	rawfile.open(path);
	if( rawfile.is_open() ) { 
		/* read the amount of objects the file contains */
		rawfile >> numObjects;

		/* make sure the line ends with a \n */		
		rawfile.get(nl);
		if(nl != '\n') throw std::string("IllegalRAWFileException");

		for(int i = 0; i < numObjects; i++) {
			/* Read the objects position */
			rawfile >> pos.x >> pos.y >> pos.z;

			/* make sure the line ends with a \n */
			rawfile.get(nl);
			if(nl != '\n') throw std::string("IllegalRAWFileException");

			/* Read the amount of triangles of this object */
			rawfile >> numTriangles;
			
			rawfile.get(nl);
			if(nl != '\n') throw std::string("IllegalRAWFileException");

			/* if the amount was 0, then something is obviously wrong */
			if(numTriangles == 0) throw std::string("IllegalRAWFileException"); 

			vertexData = new float[numTriangles*12];
			colorData = new float[numTriangles*12];

			for(int j = 0; j < numTriangles*12; j++){
				/* if there wasn't enough data or other error */
				if(rawfile.fail()) throw std::string ("GenericIOException");
				if(j%4 == 3) vertexData[j] = 1;
				else{
					rawfile >> vertexData[j];
				
					/* if a newline appeared before reading all data */
					rawfile.get(nl);
					if(nl == '\n'){ if(j+2 != numTriangles*12) { throw std::string("IllegalRAWFileException"); } }
				}
			}
			for(int j = 0; j < numTriangles *12; j++){
				/* if there wasn't enough data or other error */				
				if(rawfile.fail()) throw std::string ("GenericIOException");
				if(j%4 == 3){
					colorData[j] = 1;
				}else{
					rawfile >> colorData[j];
					if(colorData[j] < 0 || colorData[j] > 255) throw std::string("IllegalRAWFileException");
					colorData[j] /= 255;
					
					/* if a newline appeared before reading all data */					
					rawfile.get(nl);
					if(nl == '\n'){ if(j+2 != numTriangles*12) throw std::string("IllegalRAWFileException"); }
				}
			}

			/* Add object to the scene */
			GraphicalObject * object = new GraphicalObject(vertexData, numTriangles*12, colorData, numTriangles*12); 
			object->translate(pos);
			scene->get3DSpace()->addObject(object); 
	}
	return scene;
	
	}else{
		throw std::string("RAWFileNotFoundException");
	}
}
