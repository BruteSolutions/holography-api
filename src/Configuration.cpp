#include <iostream>
#include <fstream>
#include "Shared.h"
#include "Configuration.h"
using namespace std;

/**
 * Constructs a new Configuration object with the specified position, direction
 * and conversion factor.
 * @param _pos the position of the projector.
 * @param _dir the direction of the projector.
 * @param _factor the conversion factor used by the ColorTranslator object.
 */
Configuration::Configuration( Vec3 _pos, Vec3 _dir, Vec3 _factor ){
    pos = _pos;
    dir = _dir;
    factor = _factor;
}

/**
 * Returns the position of the projector.
 * @return pos a vector containing the position of the projector.
 */
Vec3 Configuration::getPosition(){
    return pos;
}

/**
 * Returns the direction of the projector.
 * @return dir a vector containing the direction of the projector.
 */
Vec3 Configuration::getDirection(){
    return dir;
}

/**
 * Returns the conversion factor of the color translator.
 * @return factor a vector containing the conversion factor of the color
 * translator.
 */
Vec3 Configuration::getColorTranslatorFactor(){
    return factor;
}

/**
 * Writes the contents of this object to the specified file stream.
 * @param os the output stream.
 * @throws GenericIOException if the stream is not open or if writing to the
 * stream fails.
 */
void Configuration::writeToStream( std::ofstream& os ) throw ( std::string )  {
    if( !os.is_open() ) throw( string( "GenericIOException" ) );
    os.exceptions( ofstream::failbit | ofstream::eofbit );    
    try{    
        os << factor.x << factor.y  << factor.z;
        os << pos.x << pos.y  << pos.z;
        os << dir.x << dir.y  << dir.z;
    }
    catch( ofstream::failure e ){
        if( os.fail() ) throw( string( "GenericIOException" ) );
    }
}

/**
 * Reads and constructs a new Configuration object from the specified file
 * stream.
 * @param is the input stream.
 * @return a new Configuration object from the contents read from the file
 * stream.
 * @throws GenericIOException if the stream is not open.
 * @throws InsufficientDataException if not all of the data sufficient for
 * constructing a new Configuration object can be read from the stream.
 * @throws IllegalFormatException if the stream data does not match the expected
 * format.
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
