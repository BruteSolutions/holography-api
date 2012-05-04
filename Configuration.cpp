//============================================================================
// Name        : Configuration.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include "Shared.h"
#include "Configuration.h"
using namespace std;


//int main () {
////  ifstream file ("example.bin", ios::in|ios::binary|ios::ate);
//  std::ofstream file("example.bin");
//
//  if (file.is_open())
//  {
//	  Vec3 factor = {0.123f, 0.23f, 0.8f};
//	  Configuration* conf = new Configuration(factor,factor,factor);
//	  conf->writeToStream(file);
//  }
//  else std::cout << "Unable to open file";
//
//
//  std::ifstream file2("example.bin");
//
//    if (file2.is_open())
//    {
//    	Configuration* test = Configuration::readStream(file2);
//    	std::cout << test->getDirection().x;
//
//    }
//    else std::cout << "Unable to open file";
//
//  return 0;
//}

Configuration::Configuration(Vec3 _pos, Vec3 _dir, Vec3 _factor){
   pos = _pos;
   dir = _dir;
   factor = _factor;
}

Vec3 Configuration::getPosition(){
   return pos;
}

Vec3 Configuration::getDirection(){
   return dir;
}
Vec3 Configuration::getColorTranslatorFactor(){
   return factor;
}
void Configuration::writeToStream(std::ofstream& os){
	os << factor.x << factor.y  << factor.z;
	os << pos.x << pos.y  << pos.z;
	os << dir.x << dir.y  << dir.z;
}
Configuration* Configuration::readStream(std::ifstream& is){
	Vec3 Tfactor;
	Vec3 Tpos;
	Vec3 Tdir;
	is >> Tfactor.x >> Tfactor.y  >> Tfactor.z;
	is >> Tpos.x >> Tpos.y  >> Tpos.z;
	is >> Tdir.x >> Tdir.y  >> Tdir.z;
   return new Configuration(Tpos, Tdir, Tfactor);
}
