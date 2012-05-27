#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <glload/gl_3_3.h>
#include <GL/glut.h>
#include "Shared.h"
#include "Configuration.h"
#include "ColorTranslator.h"
#include "UniversalConfiguration.h"
#include "ConfigurationHandler.h"

/**
 * Saves the configurations specified by the UniversalConfiguration object to a file specified by path. 
 * @param uc The UniversalConfiguration to be saved
 * @param path Path to where the configuration is supposed to be saved.
 */
void ConfigurationHandler::save( UniversalConfiguration *uc, char * path ){
    std::ofstream os( path );
    uc->writeToStream( os );
    os.close();
}

/**
 * Loads the configurations in the file identified by path and returns them in a UniversalConfiguration object. 
 * @param path Path to the configuration file
 * @return UniversalConfiguration The UniversalConfiguration object created
 */
UniversalConfiguration* ConfigurationHandler::load( char * path )  throw (std::string ) {
    //Check that the configuration we're trying to load actually exists
    std::ifstream ifile( path );
    if( ifile.fail() ) throw( std::string( "FileNotFoundException" ) );

    std::ifstream is( path );
    UniversalConfiguration* uc = UniversalConfiguration::readStream( is );
    is.close();
    return uc;
}

