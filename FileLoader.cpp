#include <stdio.h>
#include <string.h>
#include "FileLoader.h"
#include "Scene.h"

/**
 * Loads a file, and from which creates a Scene object.
 * 
 **/ 
Scene FileLoader::loadFile(string path)
{
	switch(theRightFileType(path))
	{
        case -1: // Faild filetype.
          puts("Not a valid file type");
          throw 255;
        case 1: // Filetype X3D
          // Call the X3D fileloader and return its result.
          return X3DLoader.loadFile(path);
        default: // should not be reachable, method call died.
          puts("Method to determine filetype crashed.");
          throw 254;
        }
}

int FileLoader::theRightFileType(string path)
{
  char dot = '.';
  int i = 0;
  while(path[i] != dot)
    {
      if(i > path.length())
        return -1;
      i++;
    }
  // i should now be where first . occures (and hence filetype)
  char[path.length()-i] filetype;
  int count = 0; 
  while(i > path.length())
    {
      filetype[count] = path[i];
      i++;
      count++;
    }
  // now filetype should contain the filetype ready for getting.

  string output = filetype;
  return determineNumberFromFiletype(output);
}

int FileLoader::determineNumberFromFiletype(string filetype)
{
  if(filetype.compare(".X3D") || filetype.compare(".x3d"))
    return 1;
  else
    return -1;
}

