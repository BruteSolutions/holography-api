#include <string>
#include "FileLoader.h"
#include "RawLoader.h"
#include "X3DLoader.h"
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
        	return X3DLoader::loadFile(path);
        default: // Whenever a filetype is not recognized
		std::cout << "returned " << checkFileExtension(path) << std::endl;
        	throw "IllegalFiletypeException";
		
    };
}
/**
 * Checks if the specified file has a valid file extension
 * @returns an int representing which file extension was present, if a unknown
 * file extension was present return -1.
 */
int FileLoader::checkFileExtension(std::string path) {
	std::cout << "hej3" << std::endl;
	char dot = '.';
	int i = 0;
	while(path[i] != dot) {
    	if(i > path.length())
        	return -1;
    	i++;
    }
    
	// i should now be at where the first '.' occures (and hence file extension)
	char* fileExtension = new char[path.length()-i+1];
std::cout << " path.length-i " << (path.length()-i+1) << std::endl;
	int count = 0; 
	std::cout << "count " << count << " i " << i << std::endl;
	while(i < path.length()+1) {
    	fileExtension[count] = path[i];
    	i++;
    	count++;
  }
//	fileExtension
	// now fileExtension should contain the file extension of the file.
	std::cout << "count " << count << " i " << i << std::endl;
	std::string output = fileExtension;
	std::cout << "hej3" << std::endl;
	return getFileExtensionCode(output);
}
/**
 * Get the code representing the file extension
 * @param fileExtension will be compared internally with known file extensions
 * @returns an int representing which file extension was present, if a unknown
 * file extension was present return -1.
 */

int FileLoader::getFileExtensionCode(std::string fileExtension) {
	std::cout << "hejt" << fileExtension << "lol"<< std::endl;
	if(!fileExtension.compare(".X3D") || !fileExtension.compare(".x3d")){
		std::cout << "hejt" << fileExtension << "lol"<< std::endl;
	    return 1;
	}else if (!fileExtension.compare(".bs") || !fileExtension.compare(".BS")){
			return 0;
	}else{
		return -1;
	}
}

