#ifndef __X3DLOADER_H
#define __X3DLoader_H
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

struct Vec3Int {
    int x, y, z;
};

class X3DLoader : FileLoader {
public:
    static Scene* loadFile(std::string path);

private:
    /*
    * input is all the coordIndexes that should be copied into faceVector
    * if we are reading multiple shapes the coordindex should tell this method
    * where the coordindex for the next shape should start.
    */
    static void copyCoordIndex(const char* input, std::vector<Vec3Int> *faceVector, int coordOffset);
    static void copyPoints(const char* input, std::vector<Vec4> *pointVector);
};

#endif
