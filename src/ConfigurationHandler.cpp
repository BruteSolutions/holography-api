#include <fstream>
#include <iostream>
#include <vector>

#include "Shared.h"
#include "Configuration.h"
#include "ColorTranslator.h"
#include "UniversalConfiguration.h"
#include "ConfigurationHandler.h"
using namespace std;

/* Saves the configurations specified by the UniversalConfiguration object to a file specified by path. 
 * @param uc The UniversalConfiguration to be saved
 * @param path Path to where the configuration is supposed to be saved.
 */
void ConfigurationHandler::save( UniversalConfiguration uc, string path ){
    ofstream os( path );
    uc.writeToStream( os );
    os.close();
}

/* Loads the configurations in the file identified by path and returns them in a UniversalConfiguration object. 
 * @param path Path to the configuration file
 * @return UniversalConfiguration The UniversalConfiguration object created
 */
UniversalConfiguration ConfigurationHandler::load( string path )  throws ( std::string ) {
    //Check that the configuration we're trying to load actually exists
    std::ifstream ifile( path );
    if( ifile.fail() ) throw( string( "FileNotFoundException" ) );
   
    ifstream is( path );
    UniversalConfiguration* uc = UniversalConfiguration::readStream( is );
    is.close();
    return *uc;
}

