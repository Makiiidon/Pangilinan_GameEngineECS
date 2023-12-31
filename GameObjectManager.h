#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "AGameObject.h"

class EditorAction;

class GameObjectManager
{
public:
	typedef std::string String;
	typedef std::vector<AGameObject*> List;
	typedef std::unordered_map<String, AGameObject*> HashTable;

	void applyEditorAction(EditorAction* action);

	enum PrimitiveType {
		TEXTURED_CUBE,
		CUBE,
		PLANE,
		SPHERE,
		PHYSICS_CUBE,
		PHYSICS_PLANE
	};

	static GameObjectManager* getInstance();
	static void initialize();
	static void destroy();

	AGameObject* findObjectByName(String name);
	List getAllObjects();
	int activeObjects();
	void updateAll();
	void renderAll(int viewportWidth, int viewportHeight);
	void addObject(AGameObject* gameObject);
	void createObject(PrimitiveType type);
	void deleteObject(AGameObject* gameObject);
	void deleteAllObjects();
	void deleteObjectByName(String name);
	void setSelectedObject(String name);
	void setSelectedObject(AGameObject* gameObject);
	AGameObject* getSelectedObject();

	void saveEditStates();
	void restoreEditStates();

	void createObjectFromFile(String objectName, AGameObject::PrimitiveType objectType, Vector3D position, Vector3D rotation, Vector3D scale, String path, float mass, bool hasGravity);

private:
	GameObjectManager();
	~GameObjectManager();
	GameObjectManager(GameObjectManager const&) {};             // copy constructor is private
	GameObjectManager& operator=(GameObjectManager const&) {};  // assignment operator is private*/
	static GameObjectManager* sharedInstance;

	HashTable gameObjectMap;
	List gameObjectList;

	AGameObject* selectedObject = NULL;
};

