/*
 * ConfigurationHandler.cpp
 *
 *  Created on: May 3, 2012
 *      Author: tompet
 */
#include <fstream>
#include <iostream>
#include <vector>
#include "Shared.h"
#include "ColorTranslator.h"
#include "UniversalConfiguration.h"
using namespace std;

/* Saves the configurations specified by the UniversalConfiguration object to a file specified by path. 
 * Throws IOException.
 */
static void save(UniversalConfiguration uc, String path) throw(std::string){
    ofstream file(path);
    if(!file.is_open())
        throw(string("IOException"));
    uc.writeToStream(file);
    file.close();
}

/* Loads the configurations in the file identified by path and returns them in a UniversalConfiguration object. 
 * If the loading fails, an IOException will be thrown.
 */
static UniversalConfiguration load(String path) throw(std::string){
    ifstream file(path);
    if(!file.is_open())
        throw(string("IOException");
    UniversalConfiguration* uc = UniversalConfiguration::readStream(file);
    file.close();
    return uc;
}
