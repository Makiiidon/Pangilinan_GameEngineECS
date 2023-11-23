#pragma once
#include <string>
#include <vector>

#include "AComponent.h"
#include "Vector3D.h"
#include "Matrix4x4.h"

class VertexShader;
class PixelShader;
class GameObjectManager;

class AGameObject
{

public:
	AGameObject(std::string name);
	~AGameObject();

	struct AQuaternion {
		float w = 0.0f;
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
	};

	typedef std::string String;
	typedef std::vector<AComponent*> ComponentList;

	// Abstract Methods
	virtual void update(float deltaTime) = 0;
	virtual void draw(int width, int height) = 0;

	void setPosition(float x, float y, float z);
	void setPosition(Vector3D pos);
	Vector3D getLocalPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	Vector3D getLocalScale();

	bool isEnabled();
	void setEnabled(bool enabled);

	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rot);
	Vector3D getLocalRotation();

	void attachComponent(AComponent* component);
	void detachComponent(AComponent* component);

	AComponent* findComponentByName(String name);
	AComponent* findComponentOfType(AComponent::ComponentType type, String name);
	ComponentList getComponentsOfType(AComponent::ComponentType type);
	ComponentList getComponentsOfTypeRecursive(AComponent::ComponentType type);

	// openGL matrix to our matrix implementation
	void recomputeMatrix(float matrix[16]);
	// our matrix implementation to openGL matrix
	float* getPhysicsLocalMatrix();
	void updateLocalMatrix(); //updates local matrix based from latest position, rotation, and scale.
	float* getRawMatrix();

	std::string getName();

	struct Vertex {
		Vector3D position;
		Vector3D color;
		Vector3D color2;
	};

	_declspec(align(16)) //make CBData a size of 16-bytes.
		struct CBData {
		Matrix4x4 worldMatrix;
		Matrix4x4 viewMatrix;
		Matrix4x4 projMatrix;
		float time;
	};

protected:
	std::string name;
	Vector3D localPosition;
	Vector3D localScale;
	AQuaternion orientation;
	Vector3D localRotation;
	Matrix4x4 localMatrix;

	ComponentList componentList;

	bool overrideMatrix = false;

private:
	bool enabled = true;
	friend class GameObjectManager;
};

