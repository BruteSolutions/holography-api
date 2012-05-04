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



UniversalConfiguration::UniversalConfiguration(vector<Configuration>* cs, ColorTranslator* ct){
	configurations = *cs;
	colorTrans = ct;
}
vector<Configuration> UniversalConfiguration::getProjectorConfigurations(){
	return configurations;
}
ColorTranslator* UniversalConfiguration::getColorTranslator(){
	return colorTrans;
}
UniversalConfiguration* UniversalConfiguration::readStream(ifstream& is){
	Vec3 temp;
	std::vector<Configuration> temp_configurations;
	int configSize;

	is >> temp.x >> temp.y >> temp.z;
	is >> configSize;
	for(int i = 0; i<configSize; i++){
		temp_configurations.push_back(*Configuration::readStream(is));
	}
	return new UniversalConfiguration(&temp_configurations, new ColorTranslator(temp));
}
void UniversalConfiguration::writeToStream(ofstream& os){
	os << colorTrans->getConversionFactor().x << colorTrans->getConversionFactor().y << colorTrans->getConversionFactor().z;
	os << configurations.size();
	for(vector<Configuration>::size_type i = 0; i<configurations.size(); i++){
		configurations[i].writeToStream(os);
	}
}
