#ifndef __FILELOADER_H
#define __FILELOADER_H
#include <string>
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include "Scene.h"

class FileLoader {
public:
    static Scene* loadFile(std::string path);

private:
    static int theRightFileType(std::string path);
    static int determineNumberFromFiletype(std::string path);
};

#endif
