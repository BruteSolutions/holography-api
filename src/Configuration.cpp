#include <iostream>
#include <fstream>
#include "Shared.h"
#include "Configuration.h"
using namespace std;

/* Constructs a Configuration object with the given parameters as instance variables. 
 * @param _pos the position value of the Configuration object
 * @param _dir the direction value of the Configuration object
 * @param _factor the factor value of the Configuration object
 */
Configuration::Configuration( Vec3 _pos, Vec3 _dir, Vec3 _factor ){
    pos = _pos;
    dir = _dir;
    factor = _factor;
}

/* Returns the ColorTranslator that should be used by the projector described. 
 * Returns the position of the projector.
 * @return pos the position of the projector
 */
Vec3 Configuration::getPosition(){
    return pos;
}

/* Returns the direction of the projector.
 * @return dir the direction of the projector
 */
Vec3 Configuration::getDirection(){
    return dir;
}

/* Returns the factor of the color translator.
 * @return factor the factor of the color translator
 */
Vec3 Configuration::getColorTranslatorFactor(){
    return factor;
}

/* Writes this object to the underlying stream. 
 * @param os the output stream
 */
void Configuration::writeToStream( std::ofstream& os ) throw ( std::string )  {
    if( !os.is_open() ) throw( string( "GenericIOException" ) );
    os.exceptions( ofstream::failbit | ofstream::eofbit );    
    try{	
        os << factor.x << " " << factor.y << " " << factor.z << "\n";
        os << pos.x << " " << pos.y << " " << pos.z << "\n";
        os << dir.x << " " << dir.y << " " << dir.z << "\n";
    }
    catch( ofstream::failure e ){
        if( os.fail() ) throw( string( "GenericIOException" ) );
    }
}

/* Reads the underlying stream and constructs a Configuration object which is returned. 
 * @param is the input stream
 * @return Configuration the configuration read.
 */
Configuration* Configuration::readStream( std::ifstream& is ) throw ( std::string ) {
    if( !is.is_open() ) throw( string( "GenericIOException" ) );
    Vec3 Tfactor, Tpos, Tdir;
    is.exceptions( ifstream::failbit | ifstream::eofbit );
    try{
        is >> Tfactor.x >> Tfactor.y  >> Tfactor.z;
        is >> Tpos.x >> Tpos.y  >> Tpos.z;
        is >> Tdir.x >> Tdir.y  >> Tdir.z;
    }
    catch( ifstream::failure e ){
	if( is.fail() ){
	     if( is.eof() ) throw( string( "InsufficientDataException" ) );
	     else throw( string( "IllegalFormatException" ) );
	  }
     }
    return new Configuration( Tpos, Tdir, Tfactor );
}
