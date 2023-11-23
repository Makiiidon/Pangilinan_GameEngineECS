#include "Vector3D.h"

#include "MathUtils.h"

Vector3D::Vector3D()
{

}

Vector3D::Vector3D(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3D::Vector3D(const Vector3D* vector)
{
	this->x = vector->x;
	this->y = vector->y;
	this->z = vector->z;
}

float Vector3D::getX() const
{
	return this->x;
}

float Vector3D::getY() const
{
	return this->y;
}

float Vector3D::getZ() const
{
	return this->z;
}

Vector3D Vector3D::convertEulerToRadians()
{
	return convertEulerToRadians({ x, y, z });
}

Vector3D Vector3D::convertRadiansToEuler()
{
	return convertRadiansToEuler({ x, y, z });
}

Vector3D::Vect Vector3D::getValues() const
{
	Vect vect = {};
	vect.x = this->x;
	vect.y = this->y;
	vect.z = this->z;

	return vect;
}

Vector3D Vector3D::lerp(const Vector3D start, const Vector3D end, float delta)
{
	Vector3D v;
	v.x = start.x * (1.0f - delta) + end.x * (delta);
	v.y = start.y * (1.0f - delta) + end.y * (delta);
	v.z = start.z * (1.0f - delta) + end.z * (delta);

	return v;
}

Vector3D Vector3D::ones()
{
	return {1.0f, 1.0f, 1.0f};
}

Vector3D Vector3D::zeros()
{
	return {0.0f, 0.0f, 0.0f};
}

Vector3D Vector3D::convertEulerToRadians(Vector3D euler)
{
	return {euler.x * MathUtils::PI / 180.0f, euler.y * MathUtils::PI / 180.0f, euler.z * MathUtils::PI / 180.0f};
}

Vector3D Vector3D::convertRadiansToEuler(Vector3D radians)
{
	return {radians.x * 180.0f / MathUtils::PI, radians.y * 180.0f / MathUtils::PI, radians.z * 180.0f / MathUtils::PI};
}

Vector3D::~Vector3D()
{
}
