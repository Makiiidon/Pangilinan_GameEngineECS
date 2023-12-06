#include "SceneReader.h"
#include <iostream>
#include <fstream>
#include "GameObjectManager.h"
#include "StringUtils.h"

typedef std::fstream FileReader;
SceneReader::SceneReader(String directory)
{
	this->directory = directory;
}

SceneReader::~SceneReader()
{
}

void SceneReader::readFromFile()
{
	String fileDir = this->directory + ".level";
	if (this->directory.find(".level") != String::npos) {
		fileDir = this->directory;
	}
	GameObjectManager::getInstance()->deleteAllObjects();
	FileReader  sceneFile;
	sceneFile.open(fileDir, std::ios::in);

	int index = 0;
	String readLine;

	String objectName;
	AGameObject::PrimitiveType objectType;
	String path;
	Vector3D position;
	Vector3D rotation;
	Vector3D scale;
	bool hasRigidbody = false;
	float mass = 0;
	bool isGravityEnabled = true;
	while (std::getline(sceneFile, readLine)) {
		if (index == 0) {
			objectName = readLine;
			index++;
		}
		else if (index == 1) { // Type
			std::vector stringSplit = StringUtils::split(readLine, '|');
			objectType = (AGameObject::PrimitiveType)std::stoi(stringSplit[1]);
			path = stringSplit[2];
			hasRigidbody = std::stof(stringSplit[3]);
			mass = std::stof(stringSplit[4]);
			isGravityEnabled = std::stof(stringSplit[5]);
			if (objectType == AGameObject::PrimitiveType::CUBE && hasRigidbody) objectType = AGameObject::PrimitiveType::PHYSICS_CUBE;
			if (objectType == AGameObject::PrimitiveType::PLANE && hasRigidbody)objectType = AGameObject::PrimitiveType::PHYSICS_PLANE;
			index++;
		}
		else if (index == 2) { // Position
			std::vector stringSplit = StringUtils::split(readLine, '|');
			position = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
			index++;
		}
		else if (index == 3) { // Rotation
			std::vector stringSplit = StringUtils::split(readLine, '|');
			rotation = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
			index++;
		}
		else if (index == 4) { // Scale
			std::vector stringSplit = StringUtils::split(readLine, '|');
			scale = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
			index = 0;

			GameObjectManager::getInstance()->createObjectFromFile(objectName, objectType, position, rotation, scale, path, mass, isGravityEnabled);
		}
	}
	sceneFile.close();
}

void SceneReader::readFromYAMLFile()
{
	String fileDir = this->directory + ".unity";
	if (this->directory.find(".unity") != String::npos) {
		fileDir = this->directory;
	}
	GameObjectManager::getInstance()->deleteAllObjects();
	FileReader  sceneFile;
	sceneFile.open(fileDir, std::ios::in);

	int index = 0;
	String readLine;

	String objectName;
	AGameObject::PrimitiveType objectType = AGameObject::PrimitiveType::CUBE;
	String path;
	Vector3D position;
	Vector3D rotation;
	Vector3D scale;
	bool hasRigidbody = false;
	float mass = 0;
	bool isGravityEnabled = true;

	bool isGameObject = false, physics = false;
	int gameObjLineCtr = 0;
	int rigidBodyLineCtr = 0;
	bool spawnObj = false;

	int lineCtr = 1; // for debugging

	while (std::getline(sceneFile, readLine)) {
		std::vector lineSplit = StringUtils::split(readLine, '&');
		if (lineSplit[0] == "--- !u!1 ") { // If it's a game object then start process
			isGameObject = true;
			//std::cout << "Found " << readLine << "\n";
			std::cout << "----- " << lineCtr << "-----\n";

		}
		if (lineSplit[0] == "--- !u!54 ") // If there's a Rigidbody add Physics Component
		{
			hasRigidbody = true;
			rigidBodyLineCtr = 0;

		}
		if (lineSplit[0] == "--- !u!4 ") { // Transform for the scale
			gameObjLineCtr = 0;
			rigidBodyLineCtr = 0;
			//spawnObj = true;
		}

		if (isGameObject) {
			std::vector lineSplit = StringUtils::split(readLine, ':');
			//std::cout << lineSplit[0] << "\n";

			if (lineSplit[0] == "  m_Name")
			{
				std::vector innerSplit = StringUtils::split(readLine, ' ');

				objectName = lineSplit[1];
				objectName.erase(0, 1);
				std::cout << "objectName is " << objectName << "\n";
				gameObjLineCtr = 0;
				hasRigidbody = false;


			}

			if (lineSplit[0] == "  m_TagString" /*gameObjLineCtr == 1*/) {
				std::vector innerSplit = StringUtils::split(readLine, ' ');

				if (innerSplit[3] == "Kinematic") {
					objectType = AGameObject::PrimitiveType::PHYSICS_PLANE;
				}
				else if (innerSplit[3] == "Untagged")
				{
					isGameObject = false;
					gameObjLineCtr = 0;
				}
				else if (innerSplit[3] == "Spawned") {
					isGameObject = AGameObject::PrimitiveType::CUBE;

				}
				std::cout << "Tag is " << innerSplit[3] << "\n";

			}

			gameObjLineCtr++;
			

		}
		if (hasRigidbody && isGameObject) {
			rigidBodyLineCtr++;
		}
		if (spawnObj) {
			//GameObjectManager::getInstance()->createObjectFromFile(objectName, objectType, position, rotation, scale, path, mass, isGravityEnabled);

			spawnObj = false;
		}
		lineCtr++;
	}
	sceneFile.close();

}
