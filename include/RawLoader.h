#ifndef __RAWLOADER_H
#define __RAWLOADER_H
#include <string>
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "Scene.h"
#include "FileLoader.h"
class RawLoader : FileLoader
{
public:
	static Scene* loadFile(std::string path) throw (std::string);
	
private:

};
#endif
