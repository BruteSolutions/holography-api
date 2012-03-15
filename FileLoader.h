class FileLoader
{
public:
	static Scene loadFile(std::string Path);

private:
	static bool theRightFileType(std::string Path);
}