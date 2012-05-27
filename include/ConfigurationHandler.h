/*
 * ConfigurationHandler.h
 *
 *  Created on: May 4, 2012
 *      Author: fericss
 */

#ifndef CONFIGURATIONHANDLER_H_
#define CONFIGURATIONHANDLER_H_
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <glload/gl_3_3.h>
#include <GL/glut.h>
#include "Shared.h"
#include "UniversalConfiguration.h"
#include "ColorTranslator.h"

class ConfigurationHandler{
public:
    static void save(UniversalConfiguration *uc, char * path);
    static UniversalConfiguration* load(char * path) throw(std::string);
private:   
};



#endif /* CONFIGURATIONHANDLER_H_ */
