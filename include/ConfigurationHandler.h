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
#include "Shared.h"
#include "Configuration.h"
#include "ColorTranslator.h"

class ConfigurationHandler{
public:
	static void save(UniversalConfiguration uc, std::string path);
   static UniversalConfiguration load(std::string path) throw(std::string);
private:

};



#endif /* CONFIGURATIONHANDLER_H_ */
