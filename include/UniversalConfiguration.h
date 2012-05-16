/*
 * UniversalConfiguration.h
 *
 *  Created on: Apr 27, 2012
 *      Author: fericss
 */

#ifndef UNIVERSALCONFIGURATION_H_
#define UNIVERSALCONFIGURATION_H_
#include <fstream>
#include <iostream>
#include <vector>
#include "Shared.h"
#include "Configuration.h"
#include "ColorTranslator.h"


class UniversalConfiguration{
public:
    UniversalConfiguration(std::vector<Configuration>* cs, ColorTranslator* ct);
    std::vector<Configuration> getProjectorConfigurations();
    ColorTranslator* getColorTranslator();
    static UniversalConfiguration* readStream(std::ifstream& is) throw(std::string);
    void writeToStream(std::ofstream& os) throw(std::string);

private:
    std::vector<Configuration> configurations;
    ColorTranslator* colorTrans;
};

#endif /* UNIVERSALCONFIGURATION_H_ */
