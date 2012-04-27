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

}
void UniversalConfiguration::writeToStream(ofstream& os){

}
