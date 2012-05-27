#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "Shared.h"
#include "Scene.h"
#include "RawLoader.h"

/** 
 * Parses a file and builds a scene containing graphical objects
 * @param path the filepath which to create a scene from
 * @return a Scene containing the objects specified in the file
 */
Scene* RawLoader::loadFile(std::string path) throw (std::string) {
	std::cout << "hej" << std::endl;
	std::ifstream rawfile;
	Vec3 pos;
	char nl;
	float * vertexData, * colorData;
	unsigned int numObjects, numTriangles;
	Scene * scene = new Scene();

	/* open the file */
	rawfile.open(path);
	std::cout << "hej" << std::endl;
	if( rawfile.is_open() ) { 
		/* read the amount of objects the file contains */
		rawfile >> numObjects;

		/* make sure the line ends with a \n */		
		rawfile.get(nl);
		if(nl != '\n') throw std::string("IllegalRAWFileException");
//		std::cout << "numObjects
		for(int i = 0; i < numObjects; i++) {
			/* Read the objects position */
			rawfile >> pos.x >> pos.y >> pos.z;

			/* make sure the line ends with a \n */
			rawfile.get(nl);
			if(nl != '\n') throw std::string("IllegalRAWFileException");

			/* Read the amount of triangles of this object */
			rawfile >> numTriangles;
			std::cout << "numTriangles " << numTriangles;
			rawfile.get(nl);
			if(nl != '\n') throw std::string("IllegalRAWFileException");

			/* if the amount was 0, then something is obviously wrong */
			if(numTriangles == 0) throw std::string("IllegalRAWFileException"); 
			std::cout << std::endl;
			vertexData = new float[numTriangles*12];
			colorData = new float[numTriangles*12];
			int k = 0;
			for(int triangle = 0; triangle < numTriangles; triangle++){
				for(int j = 0; j < 12; j++, k++){
					/* if there wasn't enough data or other error */
					if(rawfile.fail()){std::cout << "inside fail" << std::endl; throw std::string ("GenericIOException");}
					if(j%4 == 3) vertexData[k] = 1;
					else{
						rawfile >> vertexData[k];
						/* if a newline appeared before reading all data */
						rawfile.get(nl);
						if(nl == '\n'){ if(j+2 != 12) { throw std::string("IllegalRAWFileException"); } }
					}
						std::cout << vertexData[k] <<" ";
				}
				std::cout << std::endl;
			}
			k=0;
			for(int triangle = 0; triangle < numTriangles; triangle++){
				for(int j = 0; j < 12; j++,k++){
					/* if there wasn't enough data or other error */				
					if(rawfile.fail()){throw std::string ("GenericIOException");}
					if(j%4 == 3){
						colorData[k] = 1;
					}else{
						rawfile >> colorData[k];
						if(colorData[k] < 0 || colorData[k] > 255) throw std::string("IllegalRAWFileException");
						colorData[k] /= 255;
					
						/* if a newline appeared before reading all data */					
						rawfile.get(nl);
						if(nl == '\n'){ if(j+2 != 12){ throw std::string("IllegalRAWFileException"); }}
					}
						std::cout << colorData[j] <<" ";
				}
			std::cout << std::endl;			

			}
			for(int z = 0; z < numTriangles*12; z ++){
				std::cout << vertexData[z] << " ";
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
