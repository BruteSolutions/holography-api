/*
 * UniversalConfiguration.cpp
 *
 *  Created on: Apr 27, 2012
 *      Author: fericss
 */

#include <fstream>
#include <iostream>
#include <vector>
#include "Shared.h"
#include "Configuration.h"
#include "ColorTranslator.h"
#include "UniversalConfiguration.h"
using namespace std;



UniversalConfiguration::UniversalConfiguration(vector<Configuration> cs, ColorTranslator ct){
	configurations = cs;
	colorTrans = ct;
}
vector<Configuration> UniversalConfiguration::getProjectorConfigurations(){
	return configurations;
}
ColorTranslator* UniversalConfiguration::getColorTranslator(){
	return &colorTrans;
}
UniversalConfiguration* UniversalConfiguration::readStream(ifstream& is){
   Vec3 Tfactor, Tpos, Tdir;
   is >> Tfactor.x >> Tfactor.y  >> Tfactor.z;
   is >> Tpos.x >> Tpos.y  >> Tpos.z;
   is >> Tdir.x >> Tdir.y  >> Tdir.z;
   is.close();
   return new UniversalConfiguration(Tpos, Tdir, Tfactor);
   
}
void UniversalConfiguration::writeToStream(ofstream& os){
   os << factor.x << factor.y  << factor.z;
   os << pos.x << pos.y  << pos.z;
   os << dir.x << dir.y  << dir.z;
   os.close();
}
