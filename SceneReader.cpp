#include "SceneReader.h"
#include "GameObjectManager.h"


void SceneReader::createObjectFromFile(std::stringstream& sceneFile)
{
	String readLine;

	String objectName;

	GameObjectManager::PrimitiveType objectType;

	Vector3D position;
	Vector3D rotation;
	Vector3D scale;
	char delimiter = ' ';
	int index = 0;
	while (std::getline(sceneFile, readLine)) {
		if (index == 0) {
			objectName = readLine;
			index++;
		}
		else if (index == 1) 
		{
			std::vector<String> stringSplit = StringUtils::split(readLine, ' ');
			objectType = (GameObjectManager::PrimitiveType)std::stoi(stringSplit[1]);
			index++;
		}
		else if (index == 1)
		{
			std::vector<String> stringSplit = StringUtils::split(readLine, ' ');
			position = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
			index++;
		}
		else if (index == 1)
		{
			std::vector<String> stringSplit = StringUtils::split(readLine, ' ');
			rotation = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
			index++;
		}
		else if (index == 1)
		{
			std::vector<String> stringSplit = StringUtils::split(readLine, ' ');
			scale = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
			index = 0;

			GameObjectManager::getInstance()->createObjectFromFile(objectName, objectType, position, rotation, scale);
		}

	}

}
