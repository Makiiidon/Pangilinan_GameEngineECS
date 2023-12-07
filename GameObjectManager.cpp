#include "GameObjectManager.h"
#include "EngineTime.h"
#include "Cube.h"
#include "Plane.h"
#include "MathUtils.h"
#include "AGameObject.h"
#include "PhysicsCube.h"
#include "PhysicsPlane.h"
#include "TexturedCube.h"
#include "EditorAction.h"
#include "ObjectRenderer.h"
#include "TextureManager.h"
#include "GraphicsEngine.h"
#include "PhysicsComponent.h"

GameObjectManager* GameObjectManager::sharedInstance = NULL;

void GameObjectManager::applyEditorAction(EditorAction* action)
{
	AGameObject* object = this->findObjectByName(action->getOwnerName());
	if (object != NULL) {
		//re-apply state
		object->recomputeMatrix(action->getStoredMatrix().getMatrix());
		object->setPosition(action->getStorePos());
		object->setRotation(action->getStoredOrientation().x, action->getStoredOrientation().y, action->getStoredOrientation().z);
		object->setScale(action->getStoredScale());

	}
}

GameObjectManager* GameObjectManager::getInstance()
{
	return sharedInstance;
}

void GameObjectManager::initialize()
{
	sharedInstance = new GameObjectManager();
}

void GameObjectManager::destroy()
{
	sharedInstance->gameObjectMap.clear();
	sharedInstance->gameObjectList.clear();
	delete sharedInstance;
}

AGameObject* GameObjectManager::findObjectByName(String name)
{
	if (this->gameObjectMap[name] != NULL) {
		return this->gameObjectMap[name];
	}
	else {
		std::cout << "Object " << name << " not found!";
		return NULL;
	}
}

GameObjectManager::List GameObjectManager::getAllObjects()
{
	return this->gameObjectList;
}

int GameObjectManager::activeObjects()
{
	return this->gameObjectList.size();
}

void GameObjectManager::updateAll()
{
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		//replace with component update
		if (this->gameObjectList[i]->isEnabled()) {
			this->gameObjectList[i]->update(EngineTime::getDeltaTime());
		}
	}
}

void GameObjectManager::renderAll(int viewportWidth, int viewportHeight)
{
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		//replace with component update
		if (this->gameObjectList[i]->isEnabled()) {
			this->gameObjectList[i]->draw(viewportWidth, viewportHeight);
		}
	}
}

void GameObjectManager::addObject(AGameObject* gameObject)
{
	if (this->gameObjectMap[gameObject->getName()] != NULL) {
		int count = 1;
		String revisedString = gameObject->getName() + " " + "(" + std::to_string(count) + ")";
		while (this->gameObjectMap[revisedString] != NULL) {
			count++;
			revisedString = gameObject->getName() + " " + "(" + std::to_string(count) + ")";
		}
		//std::cout << "Duplicate found. New name is: " << revisedString << "\n";
		gameObject->name = revisedString;
		this->gameObjectMap[revisedString] = gameObject;
	}
	else {
		this->gameObjectMap[gameObject->getName()] = gameObject;
	}

	this->gameObjectList.push_back(gameObject);
}

void GameObjectManager::createObject(PrimitiveType type)
{
	if (type == PrimitiveType::CUBE) {
		Cube* cube = new Cube("Cube");
		cube->setPosition(0.0f, 0.0f, 0.0f);
		cube->setScale(1.0f, 1.0f, 1.0f);
		this->addObject(cube);
	}

	else if (type == PrimitiveType::PLANE) {
		Plane* plane = new Plane("Plane");
		this->addObject(plane);
	}

	else if (type == PrimitiveType::TEXTURED_CUBE) {
		TexturedCube* cube = new TexturedCube("Cube_Textured");
		cube->setPosition(0.0f, 0.0f, 0.0f);
		cube->setScale(1.0f, 1.0f, 1.0f);
		this->addObject(cube);
	}

	else if (type == PrimitiveType::PHYSICS_CUBE) {
		PhysicsCube* cube = new PhysicsCube("Cube_Physics");
		this->addObject(cube);
	}

	else if (type == PrimitiveType::PHYSICS_PLANE) {
		PhysicsPlane* plane = new PhysicsPlane("Plane_Physics");
		this->addObject(plane);
	}
}

void GameObjectManager::deleteObject(AGameObject* gameObject)
{
	this->gameObjectMap.erase(gameObject->getName());

	int index = -1;
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		if (this->gameObjectList[i] == gameObject) {
			index = i;
			break;
		}
	}

	if (index != -1) {
		this->gameObjectList.erase(this->gameObjectList.begin() + index);
	}

	if (gameObject == this->selectedObject)
		this->selectedObject = nullptr;

	delete gameObject;
}

void GameObjectManager::deleteAllObjects()
{
	for (int i = 0; i < gameObjectList.size(); i++) 
	{
		delete gameObjectList[i];
	}

	selectedObject = nullptr;
	gameObjectList.clear();
	gameObjectMap.clear();
}

void GameObjectManager::deleteObjectByName(String name)
{
	AGameObject* object = this->findObjectByName(name);

	if (object != NULL) {
		this->deleteObject(object);
	}
}

void GameObjectManager::setSelectedObject(String name)
{
	if (this->gameObjectMap[name] != NULL) {
		this->setSelectedObject(this->gameObjectMap[name]);
	}
}

void GameObjectManager::setSelectedObject(AGameObject* gameObject)
{
	this->selectedObject = gameObject;
}

AGameObject* GameObjectManager::getSelectedObject()
{
	return this->selectedObject;
}

void GameObjectManager::saveEditStates()
{
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		this->gameObjectList[i]->saveEditState();
	}
}

void GameObjectManager::restoreEditStates()
{
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		this->gameObjectList[i]->restoreEditState();
	}
}

void GameObjectManager::createObjectFromFile(String objectName, AGameObject::PrimitiveType objectType, Vector3D position, Vector3D rotation, Vector3D scale, String path, float mass, bool hasGravity)
{
	if (objectType == PrimitiveType::CUBE) {
		Cube* cube = new Cube(objectName);
		cube->setPosition(position);
		cube->setRotation(rotation);
		cube->setScale(scale);
		this->addObject(cube);
	}

	else if (objectType == PrimitiveType::PLANE) {
		Plane* plane = new Plane(objectName);
		plane->setPosition(position);
		plane->setRotation(rotation);
		plane->setScale(scale);
		this->addObject(plane);
	}

	else if (objectType == PrimitiveType::TEXTURED_CUBE) {
		TexturedCube* cube = new TexturedCube(objectName);
		cube->setPosition(position);
		cube->setRotation(rotation);
		cube->setScale(scale);
		cube->getRenderer()->setRenderer(path);

		String textureString = path;
		std::wstring widestr = std::wstring(textureString.begin(), textureString.end());
		const wchar_t* texturePath = widestr.c_str();

		static_cast<TexturedCube*>(cube)->getRenderer()->setTexture(TextureManager::getInstance()->createTextureFromFile(texturePath));
		this->addObject(cube);
	}

	else if (objectType == PrimitiveType::PHYSICS_CUBE) {
		PhysicsCube* cube = new PhysicsCube(objectName);
		cube->setPosition(position);
		cube->setRotation(rotation);
		cube->setScale(scale);
		static_cast<PhysicsComponent*>(cube->findComponentByName("PhysicsComponent"+ objectName))->getRigidBody()->setMass(mass);
		static_cast<PhysicsComponent*>(cube->findComponentByName("PhysicsComponent" + objectName))->getRigidBody()->enableGravity(hasGravity);
		this->addObject(cube);
	}

	else if (objectType == PrimitiveType::PHYSICS_PLANE) {
		PhysicsPlane* plane = new PhysicsPlane(objectName);
		plane->setPosition(position);
		plane->setRotation(rotation);
		plane->setScale(scale);
		this->addObject(plane);
	}
}

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}
