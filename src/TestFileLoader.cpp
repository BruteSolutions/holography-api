#include "TestFileLoader.h"

#include "Shared.h"
#include "FileLoader.h"

TestFileLoader::TestFileLoader()
{
}

void TestFileLoader::run()
{
  FileLoader f;

  //try different methods, repeatedly
  for(int i = 0; i < 100; i++) {
    f.loadFile("CadTeapot.x3d");

    if(  f.checkFileExtension("") != -1
      || f.checkFileExtension(".garbage") != -1
    ) {
      throw(std::string("Invalid file extension handling"));
    }

    if(f.getFileExtensionCode(".garbage") != -1) {
      throw(std::string("Invalid file extension code handling"));
    }

    try
    {
      f.loadFile("gar.bage");
    }
    catch(...)
    {
      continue;
    }

    throw(std::string("Failed to indicate error on invalid file"));
  }
}
