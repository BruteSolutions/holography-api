#ifndef __X3DLOADER_H
#define __X3DLOADER_H
#include <string>
#include <vector>
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include <libxml++/libxml++.h>
#include <libxml++/parsers/textreader.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "FileLoader.h"
#include "Scene.h"
#include "Shared.h"

class X3DLoader : FileLoader {
public:
    static Scene* loadFile( std::string path ) throw ( std::string );

private:
    static void copyCoordIndex( const char* input, std::vector<Vec3Int> *faceVector, int coordOffset ) throw (std::string);
    static void copyPoints( const char* input, std::vector<Vec4> *pointVector ) throw (std::string);
};

#endif
