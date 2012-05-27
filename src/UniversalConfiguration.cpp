#include <fstream>
#include <iostream>
#include <vector>

#include "Shared.h"
#include "Configuration.h"
#include "ColorTranslator.h"
#include "UniversalConfiguration.h"
using namespace std;

/* Creates a UniversalConfiguration object with the given parameters. 
 * @param cs The vector of configurations
 * @param ct The ColorTranslator
 */
UniversalConfiguration::UniversalConfiguration( vector<Configuration> * cs, ColorTranslator * ct ){
    configurations = *cs;
    colorTrans = ct;
}

/* Returns a list of Configuration objects each describing the configurations of a projector. 
 * @return vector<Configuration> The configurationlist from the projectors.
 */
vector<Configuration> * UniversalConfiguration::getProjectorConfigurations(){
    return &configurations;
}

/* Returns the ColorTranslator object that should be used by the Display class. 
 * @return ColorTranslator The ColorTranslator 
 */
ColorTranslator* UniversalConfiguration::getColorTranslator(){
    return colorTrans;
}

/* Reads the underlying stream and constructs a UniversalConfiguration object which is returned 
 * @param is The input stream
 * @return UniversalConfiguration The constructed UniversalConfiguration object
 */
UniversalConfiguration* UniversalConfiguration::readStream( ifstream& is ) throw(std::string) {
    if( !is.is_open() ) throw ( string( "GenericIOException" ) );
    Vec3 temp;
    std::vector<Configuration> temp_configurations;
    int configSize;
    
    is.exceptions( ifstream::failbit | ifstream::eofbit );
    try{

        is >> temp.x >> temp.y >> temp.z;
        is >> configSize;
    }
    catch( ifstream::failure e ){

        if( is.fail() ){
            if( is.eof() ) { throw( string( "InsufficientDataException" ) );}
            else throw( string( "IllegalFormatException" ) );
        }
    }
   
    for(int i = 0; i<configSize; i++){
        temp_configurations.push_back( *Configuration::readStream( is ) );
    }
    return new UniversalConfiguration( &temp_configurations, new ColorTranslator( temp ) );
}

/* Writes this object to the underlying stream. 
 * @param os The output stream
 */
void UniversalConfiguration::writeToStream( ofstream& os ) throw(std::string) {
    if( !os.is_open() ) throw( string( "GenericIOException") );
    
    os.exceptions( ofstream::failbit | ofstream::eofbit ); 
    try{
    os << colorTrans->getConversionFactor().x << " " << colorTrans->getConversionFactor().y << " " << colorTrans->getConversionFactor().z << "\n";
    os << configurations.size() << "\n";
    }
    catch(ofstream::failure e){   
	if( os.fail() ) throw( string( "GenericIOException" ) );
    }
       
    for(vector<Configuration>::size_type i = 0; i<configurations.size(); i++){
        configurations[ i ].writeToStream( os );
    }
}
