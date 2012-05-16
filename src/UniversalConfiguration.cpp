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

/* Creates a UniversalConfiguration object with the given parameters. */
UniversalConfiguration::UniversalConfiguration(vector<Configuration>* cs, ColorTranslator* ct){
    configurations = *cs;
    colorTrans = ct;
}

/* Returns a list of Configuration objects each describing the configurations of a projector. */
vector<Configuration> UniversalConfiguration::getProjectorConfigurations(){
    return configurations;
}

/*  Returns the ColorTranslator object that should be used by the Display class. */
ColorTranslator* UniversalConfiguration::getColorTranslator(){
    return colorTrans;
}

/* Reads the underlying stream and constructs a UniversalConfiguration object which is returned */
UniversalConfiguration* UniversalConfiguration::readStream(ifstream& is){
    if(!is.is_open()) throw(string("GenericIOException"));
    Vec3 temp;
    std::vector<Configuration> temp_configurations;
    int configSize;
    
    is.exceptions( ifstream::failbit | ifstream::eofbit);
    try{
        is >> temp.x >> temp.y >> temp.z;
        is >> configSize;
    }
    catch(ifstream::failure e){
        if(is.fail()){
            if(is.eof()) throw(string("InsufficientDataException"));
            else throw(string("IllegalFormatException"));
        }
    }
   
    for(int i = 0; i<configSize; i++){
        temp_configurations.push_back(*Configuration::readStream(is));
    }
    return new UniversalConfiguration(&temp_configurations, new ColorTranslator(temp));
}

/* Writes this object to the underlying stream. */
void UniversalConfiguration::writeToStream(ofstream& os){
    if(!os.is_open()) throw(string("GenericIOException"));
    
    os.exceptions( ofstream::failbit | ofstream::eofbit); 
    try{
    os << colorTrans->getConversionFactor().x << colorTrans->getConversionFactor().y << colorTrans->getConversionFactor().z;
    os << configurations.size();
    }
    catch(ifstream::failure e){   
	if(is.fail()) throw(string("GenericIOException"));
    }
       
    for(vector<Configuration>::size_type i = 0; i<configurations.size(); i++){
        configurations[i].writeToStream(os);
    }
}
