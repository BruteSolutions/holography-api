#include <cstring>
#include <libxml++/libxml++.h>
#include <libxml++/parsers/textreader.h>
#include <vector>
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif 
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "X3DLoader.h"
#include "Scene.h"
#include "Shared.h"
void X3DLoader::copyPoints( const char * attrib, std::vector<Vec4> *points){
	char *pch = 0;
	bool firstRun = true;
	while(pch != NULL || firstRun){
		Vec4 tmp;
  	if(firstRun){ 
  		firstRun = false; 
  		pch = strtok((char*) attrib, " ");
  	}else{
    	pch = strtok (NULL, " ");
    	
    }
		if(pch == NULL){
    		break;
    }
    tmp.x = atof(pch);
		pch = strtok (NULL, " ");
    tmp.y = atof(pch);
    pch = strtok (NULL, " ");
		tmp.z = atof(pch);
		tmp.w = 1.0;
		points->push_back(tmp);
  
	}
}
void X3DLoader::copyCoordIndex( const char* attrib, std::vector<Vec3Int> *faces, int count){
	//printf("-------------------------\n%s\n----------------------\n", attrib);
	int x,y,z;
	char *pch = 0;
	bool firstRun = true;
	int i = 0;
	while (pch != NULL || firstRun)
  {
  	Vec3Int tmp;
  	if(firstRun){ 
  		firstRun = false; 
  		pch = strtok((char*) attrib, " ");
  	}else{
    	pch = strtok (NULL, " ");
    	
    }
		if(pch == NULL){
    		break;
    }
    tmp.x = atoi(pch) + count;
		pch = strtok (NULL, " ");
    tmp.y = atoi(pch) + count;
    pch = strtok (NULL, " ");
		tmp.z = atoi(pch) + count;
		pch = strtok (NULL, " "); //-1
		faces->push_back(tmp);
  }



}
Scene* X3DLoader::loadFile(std::string path)
{
  // Set the global C and C++ locale to the user-configured locale,
  // so we can use std::cout with UTF-8, via Glib::ustring, without exceptions.
  std::locale::global(std::locale(""));
	std::vector<Vec3Int> faces;
	std::vector<Vec4> points;

	Scene * scene = new Scene();
	float *vertexData;
	float *colorData;
	int coordIndexOffset = 0; //used if multiple shapes are the same graphical object
  try
  {
    xmlpp::TextReader reader(path.c_str());

    while(reader.read())
    {
    	//Either we create a graphical object per shape, or one graphical object of all shapes
			if(strcmp(reader.get_name().c_str(), "Shape") == 0){ //Shape
				while(reader.read()){
					if(strcmp(reader.get_name().c_str(), "Shape") == 0) { break; } //read next shape
					if(strcmp(reader.get_name().c_str(), "Apperance") == 0){ //color set everything to white
						while(reader.read())
							if(strcmp(reader.get_name().c_str(), "Apperance") == 0){ break; }
					}
					if(strcmp(reader.get_name().c_str(),"IndexedFaceSet")==0){
						if(reader.has_attributes()){
						 	 reader.move_to_first_attribute();
        					do{
					          if(strcmp(reader.get_name().c_str(), "coordIndex") == 0){
					          	copyCoordIndex(reader.get_value().c_str(), &faces, coordIndexOffset);
        						}
        					}while(reader.move_to_next_attribute());
						}
						while(reader.read()){ //skipping CADPart CADFace Shape
							if(strcmp(reader.get_name().c_str(), "Coordinate")==0){
								 if(reader.has_attributes()){
								 	 reader.move_to_first_attribute();
        					do{
					          if(strcmp(reader.get_name().c_str(), "point") == 0){
					          	copyPoints(reader.get_value().c_str(), &points);
        						}
        					}while(reader.move_to_next_attribute());
        				coordIndexOffset = points.size(); //the next time a shape is loaded it will add faces at the end
								 }
							}
							if(strcmp(reader.get_name().c_str(), "IndexedFaceSet")==0){ break; }
						}
					
					}
				}			
			}
    }
    //create a graphical object
    int size = faces.size()*12; //every face consists of 3 nodes with 4 flouts
    vertexData = new float[size];
    colorData = new float[size];
    for(int i = 0; i < size; i++){
    	colorData[i] = 0.90+i*0.001;
		if(i%4 == 3) colorData[i] = 1.0;
    }
    for(int f = 0, i = 0, j = 4, k = 8; f < faces.size(); f++, i+=12, j+=12, k+=12){
    	Vec3Int face = faces.at(f);
    	vertexData[ i ] = points.at( face.x ).x;
    	vertexData[i+1] = points.at( face.x ).y;
    	vertexData[i+2] = points.at( face.x ).z;
    	vertexData[i+3] = points.at( face.x ).w;
    	vertexData[ j ] = points.at( face.y ).x;
    	vertexData[j+1] = points.at( face.y ).y;
    	vertexData[j+2] = points.at( face.y ).z;
    	vertexData[j+3] = points.at( face.y ).w;
    	vertexData[ k ] = points.at( face.z ).x;
    	vertexData[k+1] = points.at( face.z ).y;
    	vertexData[k+2] = points.at( face.z ).z;
    	vertexData[k+3] = points.at( face.z ).w;
    }
		
    for(int i = 0; i < 1032; i+=4){
    	printf("%f %f %f %f \n", vertexData[i], vertexData[i+1], vertexData[i+2], vertexData[i+3]);
    }
    printf("%d \n", size);
    scene->get3DSpace()->addObject(new GraphicalObject(vertexData, size, colorData, size));
    
    return scene;
  }
  catch(const std::exception& e)
  {
    std::cout << "Exception caught: " << e.what() << std::endl;
    return NULL;
  }
}
