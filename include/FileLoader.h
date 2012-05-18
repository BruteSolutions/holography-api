#ifndef __FILELOADER_H
#define __FILELOADER_H
#include <string>
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include "Scene.h"

class FileLoader {
public:
    static Scene* loadFile(std::string path) throw ( std::string );

private:
    static int checkFileExtension(std::string path);
    static int getFileExtensionCode(std::string path);
};

#endif
