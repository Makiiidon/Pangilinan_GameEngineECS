#include "PhysicsComponent.h"
#include <iostream>
#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
#include "AGameObject.h"
#include "Vector3D.h"

PhysicsComponent::PhysicsComponent(String name, AGameObject* owner) : AComponent(name, AComponent::ComponentType::Physics, owner)
{

	//whenever a new physics component is initialized. Register to physics system
	PhysicsSystem* physicsSystem = BaseComponentSystem::getInstance()->getPhysicsSystem();
	physicsSystem->registerComponent(this);
	PhysicsCommon* physicsCommon = physicsSystem->getPhysicsCommon();
	PhysicsWorld* physicsWorld = physicsSystem->getPhysicsWorld();

	// Create a rigid body in the world
	Vector3D scale = this->getOwner()->getLocalScale();

	Transform transform; 
	transform.setFromOpenGL(this->getOwner()->getPhysicsLocalMatrix());
	BoxShape* boxShape = physicsCommon->createBoxShape(Vector3(scale.getX() / 2, scale.getY() / 2, scale.getZ() / 2)); //half extent
	this->rigidBody = physicsWorld->createRigidBody(transform);
	Transform zero; zero.setFromOpenGL(this->getOwner()->getPhysicsLocalMatrixZero());
	this->rigidBody->addCollider(boxShape, zero);
	this->rigidBody->updateMassPropertiesFromColliders();
	this->rigidBody->setMass(this->mass);
	this->rigidBody->setType(BodyType::DYNAMIC);

	transform = this->rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	this->getOwner()->recomputeMatrix(matrix);
}

PhysicsComponent::~PhysicsComponent()
{
	//this->rigidBody->removeCollider();
	BaseComponentSystem::getInstance()->getPhysicsSystem()->unregisterComponent(this);
	AComponent::~AComponent();
}

void PhysicsComponent::perform(float deltaTime)
{
	const Transform transform = this->rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	this->getOwner()->recomputeMatrix(matrix);
}

RigidBody* PhysicsComponent::getRigidBody()
{
	return this->rigidBody;
}
