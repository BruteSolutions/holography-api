#include <string>
#include "FileLoader.h"
#include "RawLoader.h"
//#include "X3DLoader.h"
#include "Scene.h" 

/**
 * Loads a file, and from which creates a Scene object.
 * @param path the filepath to load a file from
 * @return A Scene containing the contents acquired from the specified file
 */ 
Scene* FileLoader::loadFile(std::string path) throw ( std::string ) {
	switch(checkFileExtension(path)) {
        case 0: // Filetype BS Raw
		    return RawLoader::loadFile(path);
        case 1: // Filetype X3D
        	//return X3DLoader::loadFile(path);
        default: // Whenever a filetype is not recognized
        	throw "IllegalFiletypeException";
		
    };
}
/**
 * Checks if the specified file has a valid file extension
 * @returns an int representing which file extension was present, if a unknown
 * file extension was present return -1.
 */
int FileLoader::checkFileExtension(std::string path) {
	char dot = '.';
	int i = 0;
/*has to take last dot*/
	int lastdotpos = 0;
	while(i < path.length()) {
		if(path[i] == dot)
            lastdotpos = i;
    	i++;
    }
std::cout << lastdotpos << std::endl;
    if(lastdotpos <= 0 || lastdotpos >= path.length()-1) return -1;
	i = lastdotpos;
	// i should now be at where the first '.' occures (and hence file extension)
	char* fileExtension = new char[path.length()-i+1];
	int count = 0;  

	while(i < path.length()+1) {
    	fileExtension[count] = path[i];
    	i++;
    	count++;
  }
// now fileExtension should contain the file extension of the file.
	std::string output = fileExtension;
	return getFileExtensionCode(output);
}

/**
 * Get the code representing the file extension
 * @param fileExtension will be compared internally with known file extensions
 * @returns an int representing which file extension was present, if a unknown
 * file extension was present return -1.
 */
int FileLoader::getFileExtensionCode(std::string fileExtension) {
	if(!fileExtension.compare(".X3D") || !fileExtension.compare(".x3d")){
	    return 1;
	}else if (!fileExtension.compare(".bs") || !fileExtension.compare(".BS")){
        return 0;
	}else{
		return -1;
	}
}

