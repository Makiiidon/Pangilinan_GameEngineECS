#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "AComponent.h"

using namespace std;

class VertexShader;
class PixelShader;
class GameObjectManager;

class AGameObject
{

public:
	AGameObject(string name);
	~AGameObject();

	// Abstract Methods
	virtual void update(float deltaTime) = 0;
	virtual void draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) = 0;

	void setPosition(float x, float y, float z);
	void setPosition(Vector3D pos);
	Vector3D getLocalPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	Vector3D getLocalScale();

	bool isEnabled();
	void setEnabled(bool enabled);

	bool isGameObjectStatic();
	void setStatic(bool value);

	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rot);
	Vector3D getLocalRotation();

	// openGL matrix to our matrix implementation
	void recomputeMatrix(float matrix[16]);
	// our matrix implementation to openGL matrix
	float* getPhysicsLocalMatrix();

	void attachComponent(AComponent* component);
	void detachComponent(AComponent* component);

	AComponent* findComponentByName(string name);
	AComponent* findComponentOfType(AComponent::ComponentType type, string name);
	

	string getName();

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
	string name;
	Vector3D localPosition;
	Vector3D localScale;
	Vector3D localRotation;
	Matrix4x4 localMatrix;
	bool isStatic = false;

	std::vector<AComponent*> componentList;
	std::unordered_map<std::string, AComponent*> componentTable;

private:
	bool enabled = true;
	friend class GameObjectManager;
};

