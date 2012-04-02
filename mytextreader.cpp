// -*- C++ -*-
// kräver att man kompilerar med:
//g++ program.cpp `pkg-config libxml++-2.6 --cflags --libs`
/* main.cc
 *
 * Copyright (C) 2002 The libxml++ development team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Läser in flera shapes i en x3d fil och skapar en vertex och color array
 * som man sedan kan passera vidare in ett nytt graphical object
 *
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <libxml++/libxml++.h>
#include <libxml++/parsers/textreader.h>
#include <vector>
#include <iostream>

#ifndef SHARED_H_
#define SHARED_H_
struct Vec3Int
{
	int x,y,z;
};
struct Vec4
{
	float x,y,z,w;
};
struct Mat4
{
	float m[16];
};
#endif
void copyFloats( const char * attrib, std::vector<Vec4> *points){
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
//		pch = strtok (NULL, " "); //-1
		tmp.w = 1.0;
		points->push_back(tmp);
  
	}


}
void copyIntegers( const char* attrib, std::vector<Vec3Int> *faces, int count){
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
struct indent {
  int depth_;
  indent(int depth): depth_(depth) {};
};

std::ostream & operator<<(std::ostream & o, indent const & in)
{
  for(int i = 0; i != in.depth_; ++i)
  {
    o << "  ";
  }
  return o;
}

int main(int /* argc */, char** /* argv */)
{
  // Set the global C and C++ locale to the user-configured locale,
  // so we can use std::cout with UTF-8, via Glib::ustring, without exceptions.
  std::locale::global(std::locale(""));
	std::vector<Vec3Int> faces;
	std::vector<Vec4> points;
	float *vertexData;
	float *colorData;
	int coordIndexOffset = 0; //used if multiple shapes are the same graphical object
  try
  {
    xmlpp::TextReader reader("CadTeapot.x3d");

    while(reader.read())
    {
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
					          	copyIntegers(reader.get_value().c_str(), &faces, coordIndexOffset);
/*	printf("-----------------------\n");
  std::vector<Vec3Int>::iterator it;
  for(it = faces.begin(); it < faces.end(); it++){
  	printf("%d %d %d ", (*it).x, (*it).y, (*it).z);
  }
  printf("\n-----------------------\n");*/
        						}
        					}while(reader.move_to_next_attribute());
						}
						while(reader.read()){ //skipping CADPart CADFace Shape
							if(strcmp(reader.get_name().c_str(), "Coordinate")==0){
								 if(reader.has_attributes()){
								 	 reader.move_to_first_attribute();
        					do{
					          if(strcmp(reader.get_name().c_str(), "point") == 0){
					          	copyFloats(reader.get_value().c_str(), &points);

/*  printf("-----------------------\n");
  std::vector<Vec4>::iterator it;
  for(it = points.begin(); it < points.end(); it++){
  	printf("%f %f %f ", (*it).x, (*it).y, (*it).z);
  }
  printf("\n-----------------------\n");*/
        						}
        					}while(reader.move_to_next_attribute());
        				coordIndexOffset = points.size(); //the next time a shape is loaded it will add faces at the end
								 }
							}
							if(strcmp(reader.get_name().c_str(), "IndexedFaceSet")==0){ break; }
						}
					
					}
				}
			//read a shape in here
				/*while(reader.read()){
					if(strcmp(reader.get_name().c_str(), "
				}*/				
			}

    }
    //a face: v1, v2, v3
    //a face: x1 y1 z1 w1, x2 y2 z2 w2, x3 y3 z3 w3
    //a vertex x1 y1 z1 w1
    //a vertex float float float float
    vertexData = new float[faces.size()*12];
    colorData = new float[faces.size()*12];
    for(int i = 0; i < faces.size()*12; i++){
    	colorData[i] = 1.0;
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
    printf("%d \n", faces.size()*12);
  }
  catch(const std::exception& e)
  {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }
}

