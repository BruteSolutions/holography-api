#include <string>
#include "FileLoader.h"
class RawLoader : FileLoader
{
public:
	static Scene* loadFile(std::string Path) throw (std::string);
	
private:

};
