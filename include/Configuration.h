/*
 * Configuration.h
 *
 *  Created on: Apr 27, 2012
 *      Author: fericss
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_
#include <fstream>
#include <iostream>
#include "Shared.h"

class Configuration{
public:
    Configuration(Vec3 pos, Vec3 dir, Vec3 factor);
    Configuration();
    static Configuration* readStream(std::ifstream& is) throw(std::string);
    void writeToStream(std::ofstream& os) throw(std::string);
    Vec3 getPosition();
    Vec3 getDirection();
    Vec3 getColorTranslatorFactor();


private:
    Vec3 pos;
    Vec3 dir;
    Vec3 factor;
};
#endif /* CONFIGURATION_H_ */
