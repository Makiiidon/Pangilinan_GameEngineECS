#include "SceneWriter.h"
#include "GameObjectManager.h"
#include <fstream>
#include "StringUtils.h"
#include "TexturedCube.h"
#include "ObjectRenderer.h"
#include "PhysicsComponent.h"


void SceneWriter::setDirectory(String directory)
{
	this->directory = directory;
}

void SceneWriter::writeToFile()
{
	String fileDir = this->directory + ".level";
	if (this->directory.find(".level") != String::npos) 
	{
		fileDir = this->directory;
	}

	std::ofstream sceneFile;
	sceneFile.open(fileDir, std::ios::out);

	std::cout << "Selected file directory " << fileDir << "\n";

	GameObjectManager::List allObjects = GameObjectManager::getInstance()->getAllObjects();

	for (int i = 0; i < allObjects.size(); i++) 
	{
		sceneFile << allObjects[i]->getName() << std::endl;
		Vector3D position = allObjects[i]->getLocalPosition();
		Vector3D rotation = allObjects[i]->getLocalRotation();
		Vector3D scale = allObjects[i]->getLocalScale();
		float mass = 0;
		bool hasRigidbody = false;
		bool isGravityEnabled = true;

		if (allObjects[i]->findComponentByName("PhysicsComponent")) 
		{
			mass = static_cast<PhysicsComponent*>(allObjects[i]->findComponentByName("PhysicsComponent"))->getRigidBody()->getMass();
			hasRigidbody = true;
			isGravityEnabled = static_cast<PhysicsComponent*>(allObjects[i]->findComponentByName("PhysicsComponent"))->getRigidBody()->isGravityEnabled();
		}

		std::string path = "none";
		if (allObjects[i]->getObjectType() == AGameObject::PrimitiveType::TEXTURED_CUBE) {
			path = static_cast<TexturedCube*>(allObjects[i])->getRenderer()->getMaterialPath();
		}
			
		sceneFile << "Type:|" << allObjects[i]->getObjectType() << "|" << path << "|" << hasRigidbody << "|" << mass << "|"  << isGravityEnabled << "|" << std::endl;
		sceneFile << "Position:|"	<< position.getX()	<< "|" << position.getY() << "|"	<< position.getZ()	<< "|" << std::endl;
		sceneFile << "Rotation:|"	<< rotation.getX()	<< "|" << rotation.getY() << "|"	<< rotation.getZ()	<< "|" << std::endl;
		sceneFile << "Scale:|"		<< scale.getX()		<< "|" << scale.getY() << "|"		<< scale.getZ()		<< "|" << std::endl;
	}
	sceneFile.close();
}
