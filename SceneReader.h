#pragma once
#include <string>

class SceneReader
{
public:
	typedef std::string String;
	SceneReader(String directory);
	~SceneReader();

	void readFromFile();
	void readFromYAMLFile();

private:
	String directory;
};