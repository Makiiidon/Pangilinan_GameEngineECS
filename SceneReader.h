#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include "StringUtils.h"

class SceneReader
{
public:
	typedef std::string String;
	void createObjectFromFile(std::stringstream& sceneFile);
};

