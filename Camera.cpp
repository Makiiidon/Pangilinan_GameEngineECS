#include "Camera.h"
#include "InputSystem.h"
#include <iostream>

Camera::Camera(std::string name) : AGameObject(name)
{
	this->forwardDirection = Vector3D(1.0f, 0.0f, 1.0f);
	this->backwardDirection = Vector3D(-1.0f, 0.0f, -1.0f);

	this->setPosition(0.0f, 0.0f, -4.0f);
	//this->worldCameraMatrix.setTranslation(this->getLocalPosition());
	this->updateViewMatrix();
	InputSystem::getInstance()->addListener(this);
}

Camera::~Camera()
{
	InputSystem::getInstance()->removeListener(this);
}

void Camera::update(float deltaTime)
{
	Vector3D localPos = this->getLocalPosition();
	float x = localPos.getX();
	float y = localPos.getY();
	float z = localPos.getZ();
	float moveSpeed = 10.0f;

	if (InputSystem::getInstance()->isKeyDown('W')) {
		Vector3D direction = localMatrix.getZDirection();
		Vector3D newPos = Vector3D(
			x + direction.getX() * deltaTime * moveSpeed,
			y + direction.getY() * deltaTime * moveSpeed,
			z + direction.getZ() * deltaTime * moveSpeed);

		this->setPosition(newPos.getX(), newPos.getY(), newPos.getZ());
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('S')) {
		Vector3D direction = localMatrix.getZDirection();
		Vector3D newPos = Vector3D(
			x + direction.getX() * deltaTime * -moveSpeed,
			y + direction.getY() * deltaTime * -moveSpeed,
			z + direction.getZ() * deltaTime * -moveSpeed);

		this->setPosition(newPos.getX(), newPos.getY(), newPos.getZ());
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('A')) {
		Vector3D direction = localMatrix.getXDirection();
		Vector3D newPos = Vector3D(
			x + direction.getX() * deltaTime * -moveSpeed,
			y + direction.getY() * deltaTime * -moveSpeed,
			z + direction.getZ() * deltaTime * -moveSpeed);

		this->setPosition(newPos.getX(), newPos.getY(), newPos.getZ());
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('D')) {
		Vector3D direction = localMatrix.getXDirection();
		Vector3D newPos = Vector3D(
			x + direction.getX() * deltaTime * moveSpeed,
			y + direction.getY() * deltaTime * moveSpeed,
			z + direction.getZ() * deltaTime * moveSpeed);

		this->setPosition(newPos.getX(), newPos.getY(), newPos.getZ());
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('Q')) {
		Vector3D direction = Vector3D(0, 1, 0);
		Vector3D newPos = Vector3D(
			x + direction.getX() * deltaTime * -moveSpeed,
			y + direction.getY() * deltaTime * -moveSpeed,
			z + direction.getZ() * deltaTime * -moveSpeed);

		this->setPosition(newPos.getX(), newPos.getY(), newPos.getZ());
		this->updateViewMatrix();
	}
	else if (InputSystem::getInstance()->isKeyDown('E')) {
		Vector3D direction = Vector3D(0, 1, 0);
		Vector3D newPos = Vector3D(
			x + direction.getX() * deltaTime * moveSpeed,
			y + direction.getY() * deltaTime * moveSpeed,
			z + direction.getZ() * deltaTime * moveSpeed);

		this->setPosition(newPos.getX(), newPos.getY(), newPos.getZ());
		this->updateViewMatrix();
	}
}

void Camera::draw(int width, int height)
{
	// no-op
}

Matrix4x4 Camera::getViewMatrix()
{
	return this->viewMatrix;
}

void Camera::onKeyDown(int key)
{
}

void Camera::onKeyUp(int key)
{
}

void Camera::onMouseMove(const Point deltaPos)
{
	if (this->mouseDown) {
		Vector3D localRot = this->getLocalRotation();
		float x = localRot.getX();
		float y = localRot.getY();
		float z = localRot.getZ();

		float speed = 0.5f;
		x += deltaPos.getY() * speed;
		y += deltaPos.getX() * speed;

		this->setRotation(x, y, z);

		this->updateViewMatrix();
		Vector3D dirZ = localMatrix.getZDirection();
		Vector3D dirX = localMatrix.getXDirection();
	}
}

void Camera::onLeftMouseDown(const Point deltaPos)
{
}

void Camera::onLeftMouseUp(const Point deltaPos)
{
}

void Camera::onRightMouseDown(const Point deltaPos)
{
	this->mouseDown = true;
}

void Camera::onRightMouseUp(const Point deltaPos)
{
	this->mouseDown = false;
}

void Camera::updateViewMatrix()
{
	Matrix4x4 worldCam; worldCam.setIdentity();
	Matrix4x4 temp; temp.setIdentity();

	Vector3D localRot = this->getLocalRotation();

	temp.setRotationX(localRot.getX());
	worldCam = worldCam.multiplyTo(temp);

	temp.setRotationY(localRot.getY());
	worldCam = worldCam.multiplyTo(temp);

	temp.setTranslation(this->getLocalPosition());
	worldCam = worldCam.multiplyTo(temp);

	this->localMatrix = worldCam.clone();

	worldCam.setInverse();

	this->viewMatrix = worldCam;
}
