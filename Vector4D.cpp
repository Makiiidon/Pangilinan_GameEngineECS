#include "Vector4D.h"

Vector4D::Vector4D()
{
}

Vector4D::~Vector4D()
{
}

Vector4D::Vector4D(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4D::Vector4D(const Vector4D* vector)
{
	this->x = vector->x;
	this->y = vector->y;
	this->z = vector->z;
	this->w = vector->w;
}

void Vector4D::cross(Vector4D v1, Vector4D v2, Vector4D v3)
{
	this->x = v1.y * (v2.z * v3.w - v3.z * v2.w) - v1.z * (v2.y * v3.w - v3.y * v2.w) + v1.w * (v2.y * v3.z - v2.z * v3.y);
	this->y = -(v1.x * (v2.z * v3.w - v3.z * v2.w) - v1.z * (v2.x * v3.w - v3.x * v2.w) + v1.w * (v2.x * v3.z - v3.x * v2.z));
	this->z = v1.x * (v2.y * v3.w - v3.y * v2.w) - v1.y * (v2.x * v3.w - v3.x * v2.w) + v1.w * (v2.x * v3.y - v3.x * v2.y);
	this->w = -(v1.x * (v2.y * v3.z - v3.y * v2.z) - v1.y * (v2.x * v3.z - v3.x * v2.z) + v1.z * (v2.x * v3.y - v3.x * v2.y));
}

float Vector4D::getX()
{
	return this->x;
}

float Vector4D::getY()
{
	return this->y;
}

float Vector4D::getZ()
{
	return this->z;
}

float Vector4D::getW()
{
	return this->w;
}
