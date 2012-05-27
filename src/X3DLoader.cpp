#include <cstring>
#include <libxml++/libxml++.h>
#include <libxml++/parsers/textreader.h>
#include <vector>
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "X3DLoader.h"
#include "Scene.h"
#include "Shared.h"

/* Takes a path to an X3D-file and returns a scene containing a graphicalobject
 * built from information in the Shape brackets
 *
 * @param path is the path to the X3D-file
 * @return returns a Scene object containing the object in the file
 */
Scene* X3DLoader::loadFile( std::string path ) throw ( std::string ) {
    //Check that the file we're trying to load actually exists
   std::ifstream ifile(path);
   if( ifile.fail() ) throw( std::string( "X3DFileNotFoundException" ) );
   
    // Set the global C and C++ locale to the user-configured locale,
    // so we can use std::cout with UTF-8, via Glib::ustring, without exceptions.
    std::locale::global(std::locale(""));
    std::vector<Vec3Int> faces;
    std::vector<Vec4> points;
    Scene * scene = new Scene();
    float *vertexData;
    float *colorData;
    int coordIndexOffset = 0; //used if multiple shapes are the same graphical object
    try {
        xmlpp::TextReader reader( path.c_str() );

        while( reader.read() ) {
            //We create a graphical object by reading the Shape bracket
            if ( strcmp( reader.get_name().c_str(), "Shape" ) == 0 ) { //Shape
                while ( reader.read() ) {
                    if ( strcmp( reader.get_name().c_str(), "Shape" ) == 0 ) { break; } //Shape end bracket, read next shape
                    if ( strcmp( reader.get_name().c_str(), "Apperance" ) == 0 ) { 
                        	//the color can be found in Apperance bracket
                        while ( reader.read() )
                            if ( strcmp( reader.get_name().c_str(), "Apperance" ) == 0 ) { break; } //Apperance end bracket
                    }
                    if ( strcmp( reader.get_name().c_str(),"IndexedFaceSet" ) == 0 ) {
                        if ( reader.has_attributes() ) {
                            reader.move_to_first_attribute();
                            do {
                                if ( strcmp( reader.get_name().c_str(), "coordIndex" ) == 0 ) {
                                    copyCoordIndex( reader.get_value().c_str(), &faces, coordIndexOffset );
                                }
                                if ( strcmp( reader.get_name().c_str(), "colorIndex" ) == 0 ) {
                                	//handle color per triangle
                                }
                            } while ( reader.move_to_next_attribute() );
                        }
                        while ( reader.read() ) { //skipping CADPart CADFace Shape
                            if ( strcmp( reader.get_name().c_str(), "Coordinate" ) == 0 ) {
                                if ( reader.has_attributes() ) {
                                    reader.move_to_first_attribute();
                                    do {
                                        if( strcmp( reader.get_name().c_str(), "point" ) == 0 ) {
                                            copyPoints( reader.get_value().c_str(), &points );
                                        }
                                    } while ( reader.move_to_next_attribute() );
                                    coordIndexOffset = points.size(); //the next time a shape is loaded it will add faces at the end
                                }
                            }
                            if ( strcmp( reader.get_name().c_str(), "Color" ) == 0 ) {
                            	if ( reader.has_attributes() ) {
                            		reader.move_to_first_attribute();
                            		do {
                            			if ( strcmp( reader.get_name().c_str(), "color" ) == 0 ) {
                            				//handle color coords
                            			}
                            		} while ( reader.move_to_next_attribute() );
                                }
                            }
                            if ( strcmp( reader.get_name().c_str(), "IndexedFaceSet" ) == 0) { break; }
                        }
                    }
                }            
            }
        }
        //create a graphical object
        int size = faces.size() * 12; //every face consists of 3 nodes with 4 flouts
        if(size == 0){ // means that we didnt find data for us to load
            throw std::string("InvalidX3DFileException");
        }
        vertexData = new float[ size ];
        colorData = new float[ size ];
        int x = 0, y = 0;
        
        /* Creates the color vector, read color from the file */
        for (int i = 0; i < size; i += 4) {
            colorData[ i     ] = 1.0; 
            colorData[ i + 1 ] = 0.0; 
            colorData[ i + 2 ] = 0.0; 
            colorData[ i + 3 ] = 1.0;
            //colorData[ i + y ] = 1.0;
            x++;
            if ( x == 3 ) {
                x = 0;
                y++; 
                if (y == 4) { 
                    y = 0;
                }
            }
        }
        /* Creates the coord vector that builds triangles */
        for (int f = 0, i = 0, j = 4, k = 8; f < faces.size(); f++, i += 12, j += 12, k += 12) {
            Vec3Int face = faces.at( f );
            vertexData[ i ]     = points.at( face.x ).x;
            vertexData[ i + 1 ] = points.at( face.x ).y;
            vertexData[ i + 2 ] = points.at( face.x ).z;
            vertexData[ i + 3 ] = points.at( face.x ).w;
            std::cout << "Vertex for triangle " << f << " corner " << 0 << ": " << vertexData[ i ] << " " << vertexData[ i+1 ] << " " << vertexData[ i+2 ] <<  " " << vertexData[ i+3 ] << std::endl;
            vertexData[ j ]     = points.at( face.y ).x;
            vertexData[ j + 1 ] = points.at( face.y ).y;
            vertexData[ j + 2 ] = points.at( face.y ).z;
            vertexData[ j + 3 ] = points.at( face.y ).w;
            std::cout << "Vertex for triangle " << f << " corner " << 1 << ": " << vertexData[ j ] << " " << vertexData[ j+1 ] << " " << vertexData[ j+2 ] <<  " " << vertexData[ j+3 ] << std::endl;
            vertexData[ k ]     = points.at( face.z ).x;
            vertexData[ k + 1 ] = points.at( face.z ).y;
            vertexData[ k + 2 ] = points.at( face.z ).z;
            vertexData[ k + 3 ] = points.at( face.z ).w;
            std::cout << "Vertex for triangle " << f << " corner " << 2 << ": " << vertexData[ k ] << " " << vertexData[ k+1 ] << " " << vertexData[ k+2 ] <<  " " << vertexData[ k+3 ] << std::endl;

        }

        scene->get3DSpace()->addObject( new GraphicalObject( vertexData, size, colorData, size ) );
        
        return scene;
 
    } catch( const std::exception& e ) { // catches LIBXML++ exception 2.6
       if( e.what().find( "parse error" ) != string::npos ) throw( std::string( "IllegalX3DFileException" ) );
        /*else*/ throw std::string(e.what());
    }
}

/* Takes a Points attribute and saves its content as a vector of coordinates.
 * A face instance in the faces vector contains indices that represent the 
 * coordinates in this list. 
 *
 * @param attribute is the attribute Points read from a X3D-file
 * @param points is a vector that new coordinates are pushed to
 */
void X3DLoader::copyPoints( const char * attribute, std::vector<Vec4> *points )  throw (std::string){
    char *pch = 0;
    bool firstRun = true;
    while ( pch != NULL || firstRun ) {
        Vec4 tmp;
        if ( firstRun ) {
            firstRun = false; 
            pch = strtok( (char*) attribute, " " );
        } else {
            pch = strtok ( NULL, " " );
        }
        if ( pch == NULL ) {
            break;
        }
        
        tmp.x = atof( pch );
        pch = strtok( NULL, " " );
        tmp.y = atof( pch );
        pch = strtok( NULL, " " );
        tmp.z = atof( pch );
        tmp.w = 1.0;
        points->push_back( tmp );
    }
}

/* Takes the attribute CoordIndex in a X3D-file and reads it into the faces vector, 
 * three integer values in the attribute corresponds three different coordinates in
 * a coordinate vector, which builds a face. Every triple of integervalue is followed
 * with -1 which is discarded
 *
 * @param attribute is the attribute CoordIndex read from a X3D-file
 * @param faces is a vector that new faces are pushed to, old instances in faces will not be overridden
 * @param count states where the index should start to count from. This makes it possible to read multiple
 *              Shape brackets containing a CoordIndex each, indices start at 0 in every Shape brace
 */ 
void X3DLoader::copyCoordIndex( const char* attribute, std::vector<Vec3Int> *faces, int count )  throw (std::string){
    int x, y, z;
    char *pch = 0;
    bool firstRun = true;
    int i = 0;
    while ( pch != NULL || firstRun ) {
        Vec3Int tmp,tmp2;
        if ( firstRun ) { 
            firstRun = false; 
            pch = strtok( (char*) attribute, " " );
        } else {
            i = 0;
            pch = strtok ( NULL, " " );
        }
        
        if ( pch == NULL ) {
            break;
        }
      	
        tmp.x = atoi( pch );
        if(tmp.x == -1) throw std::string("InvalidX3DFileException");
        pch = strtok( NULL, " " );
        tmp.y = atoi( pch );
        if(tmp.y == -1) throw std::string("InvalidX3DFileException");
        pch = strtok( NULL, " " );
        tmp.z = atoi( pch );
        if(tmp.z == -1) throw std::string("InvalidX3DFileException");
        pch = strtok( NULL, " "); //face index value or -1
        tmp2.z = atoi( pch );
        if(tmp2.z >= 0){ //square
        	pch = strtok( NULL, " "); //-1
        	if(atoi( pch ) != -1) throw std::string("InvalidX3DFileException");
        	tmp2.x = tmp.x;
        	tmp2.y = tmp.z;
        	i=1;
        }//else triangle
        
		faces->push_back( {tmp.x+count,tmp.y+count,tmp.z+count} );
        if(i==1){ //square, add another face
			faces->push_back( {tmp2.x+count,tmp2.y+count,tmp2.z+count} );
        }
    }
}


