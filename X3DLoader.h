#include <string>
#include <vector>
#include "FileLoader.h"
#include "Scene.h"
#include "Shared.h"
struct Vec3Int
{
	int x,y,z;
};
class X3DLoader : FileLoader
{
public:
	static Scene loadFile(std::string Path);
	
private:
	/*
	* input is all the coordIndexes that should be copied into faceVector
	* if we are reading multiple shapes the coordindex should tell this method
	* where the coordindex for the next shape should start.
	*/
	static void copyCoordIndex(char* input, std::vector<Vec3Int> faceVector, int coordOffset);
	static void copyPoints(char* input, std::vector<Vec4> pointVector);
}
