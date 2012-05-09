/*
 * ConfigurationHandler.h
 *
 *  Created on: May 3, 2012
 *      Author: tompet
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
	static void save(UniversalConfiguration uc, String path) throw(std::string);
	static void load(String path) throw(std::string);
};

#endif /* CONFIGURATIONHANDLER_H_ */
