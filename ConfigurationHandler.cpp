/*
 * ConfigurationHandler.cpp
 *
 *  Created on: May 4, 2012
 *      Author: fericss
 */

#include <fstream>
#include <iostream>
#include <vector>
#include "Shared.h"
#include "Configuration.h"
#include "ColorTranslator.h"
#include "UniversalConfiguration.h"
#include "ConfigurationHandler.h"
using namespace std;

void ConfigurationHandler::save(UniversalConfiguration uc, string path){
	ofstream os("bah");
	uc.writeToStream(os);
	os.close();
}

UniversalConfiguration ConfigurationHandler::load(string path){
	ifstream is("bah");
	UniversalConfiguration* uc = UniversalConfiguration::readStream(is);
	is.close();
	return *uc;
}
