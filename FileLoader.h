#include <string>
#include "Scene.h"
class FileLoader
{
public:
	static Scene loadFile(std::string Path);

private:
	static int theRightFileType(std::string Path);
        static int determineNumberFromFiletype(std::string Path);
}
