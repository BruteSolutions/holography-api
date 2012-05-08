#include <fstream>
#include <iostream>
#include <vector>
#include "Shared.h"
#include "Configuration.h"
#include "ColorTranslator.h"
#include "UniversalConfiguration.h"
using namespace std;


/* Creates a UniversalConfiguration object with the given parameters. */
UniversalConfiguration::UniversalConfiguration(vector<Configuration> cs, ColorTranslator ct){
    configurations = cs;
    colorTrans = ct;
}

/* Returns a list of Configuration objects each describing the configurations of a projector. */
vector<Configuration> UniversalConfiguration::getProjectorConfigurations(){
    return configurations;
}

/*  Returns the ColorTranslator object that should be used by the Display class. */
ColorTranslator* UniversalConfiguration::getColorTranslator(){
    return &colorTrans;
}

/* Reads the underlying stream and constructs a UniversalConfiguration object which is returned */
UniversalConfiguration* UniversalConfiguration::readStream(ifstream& is){
    Vec3 Tfactor, Tpos, Tdir;
    is >> Tfactor.x >> Tfactor.y  >> Tfactor.z;
    is >> Tpos.x >> Tpos.y  >> Tpos.z;
    is >> Tdir.x >> Tdir.y  >> Tdir.z;
    is.close();
    return new UniversalConfiguration(Tpos, Tdir, Tfactor);
   
}
/* Writes this object to the underlying stream. */
void UniversalConfiguration::writeToStream(ofstream& os){
    os << factor.x << factor.y  << factor.z;
    os << pos.x << pos.y  << pos.z;
    os << dir.x << dir.y  << dir.z;
    os.close();
}
