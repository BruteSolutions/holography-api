#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
#include "Shared.h"
#include "RawLoader.h"

/* 
 * documentation
 *
 */
static Scene* loadFile(std::string path) throw (std::string) {
	std::ifstream rawfile;
	Vec3 pos;
	char nl;

	
	float * vertexData, * colorData;
	unsigned int numObjects, numTriangles;
	rawfile.open(path);
	if(rawfile.is_open()){
		rawfile >> numObjects;
		rawfile.get(nl);
		if(nl != '\n') throw std::string("IllegalRAWFileException");
		for(int i = 0; i < numObjects; i++){
			rawfile >> pos.x >> pos.y >> pos.z;
			rawfile.get(nl);
			if(nl != '\n') throw std::string("IllegalRAWFileException");
			rawfile >> numTriangles;
			rawfile.get(nl);
			if(nl != '\n') throw std::string("IllegalRAWFileException");

			if(numTriangles == 0) throw std::string("IllegalRAWFileException"); 

			vertexData = new float[numTriangles*12];
			colorData = new float[numTriangles*12];

			for(int j = 0; j < numTriangles*12; j++){
				if(rawfile.fail()) throw std::string ("GenericIOException");
				if(j%4 == 3) vertexData[j] = 1;
				else{
				rawfile >> vertexData[j];
				rawfile.get(nl);
				if(nl == '\n'){ if(j+2 != numTriangles*12) { throw std::string("IllegalRAWFileException"); } }
				}
			}
			for(int j = 0; j < numTriangles *12; j++){
				if(rawfile.fail()) throw std::string ("IllegalRAWFileException");
				if(j%4 == 3){
					colorData[j] = 1;
				}else{
					rawfile >> colorData[j];
					if(colorData[j] < 0 || colorData[j] > 255) throw std::string("IllegalRAWFileException");
					colorData[j] /= 255;
				rawfile.get(nl);
				if(nl == '\n'){ if(j+2 != numTriangles*12) throw std::string("IllegalRAWFileException"); }
				}
			}

			//TODO tmp graphical object som vi sätter pos på och sen lägger i scene
			//Scene * scene = new Scene();
			//GraphicalObject * object = new GraphicalObject(vertexData, numTriangles*12, colorData, numTriangles*12); 
			//object.translate(pos);
			//return scene.addObject(object); 
			return NULL;
		}
	
	}else{
		throw std::string("RAWFileNotFoundException");
	}
}
