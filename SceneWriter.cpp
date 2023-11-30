#include "SceneWriter.h"
#include "GameObjectManager.h"
#include <fstream>
#include "StringUtils.h"


void SceneWriter::setDirectory(String directory)
{
	this->directory = directory;
}

void SceneWriter::writeToFile()
{
	String fileDir = this->directory + ".json";
	if (this->directory.find(".json") != String::npos) 
	{
		fileDir = this->directory;
	}

	std::ofstream sceneFile;
	sceneFile.open(fileDir, std::ios::out);

	std::cout << "Selected filename" << fileDir << "\n";

	GameObjectManager::List allObjects = GameObjectManager::getInstance()->getAllObjects();

	for (int i = 0; i < allObjects.size(); i++) 
	{
		sceneFile << allObjects[i]->getName() << std::endl;
		Vector3D position = allObjects[i]->getLocalPosition();
		Vector3D rotation = allObjects[i]->getLocalRotation();
		Vector3D scale = allObjects[i]->getLocalScale();

		sceneFile << "Type: " << allObjects[i]->getObjectType() << std::endl;
		sceneFile << "Position: "	<< position.getX()	<< " " << position.getY() << " "	<< position.getZ()	<< " " << std::endl;
		sceneFile << "Rotation: "	<< rotation.getX()	<< " " << rotation.getY() << " "	<< rotation.getZ()	<< " " << std::endl;
		sceneFile << "Scale: "		<< scale.getX()		<< " " << scale.getY() << " "		<< scale.getZ()		<< " " << std::endl;
	}
	sceneFile.close();
}
