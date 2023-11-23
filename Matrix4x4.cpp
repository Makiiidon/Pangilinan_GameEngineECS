#include "Matrix4x4.h"

#include "MathUtils.h"


Matrix4x4::Matrix4x4()
{
}

Matrix4x4::~Matrix4x4()
{
}

void Matrix4x4::setIdentity()
{
	//set array as zeros
	this->matrixInitialize();
	this->matrix[0][0] = 1;
	this->matrix[1][1] = 1;
	this->matrix[2][2] = 1;
	this->matrix[3][3] = 1;
}

void Matrix4x4::setMatrix(const Matrix4x4 matrix)
{
	::memcpy(this->matrix, matrix.matrix, sizeof(float) * 16);
}

void Matrix4x4::setMatrix(float matrix[4][4])
{
	::memcpy(this->matrix, matrix, sizeof(float) * 16);
}

Matrix4x4 Matrix4x4::clone()
{
	Matrix4x4 copy;
	::memcpy(copy.matrix, this->matrix, sizeof(float) * 16);

	return copy;

}

void Matrix4x4::setTranslation(const Vector3D translation)
{
	this->setIdentity();
	Vector3D::Vect vect = translation.getValues();
	this->matrix[3][0] = vect.x;
	this->matrix[3][1] = vect.y;
	this->matrix[3][2] = vect.z;
}

void Matrix4x4::setScale(const Vector3D scale)
{
	this->setIdentity();
	Vector3D::Vect vect = scale.getValues();
	this->matrix[0][0] = vect.x;
	this->matrix[1][1] = vect.y;
	this->matrix[2][2] = vect.z;
}

/**
 * \brief 
 * \param x Euler Angle rotation of x-axis
 */
void Matrix4x4::setRotationX(float x)
{
	const float x_rad = x * MathUtils::PI / 180.0f;
	this->setIdentity();
	this->matrix[1][1] = cos(x_rad);
	this->matrix[1][2] = sin(x_rad);
	this->matrix[2][1] = -sin(x_rad);
	this->matrix[2][2] = cos(x_rad);
}

/**
 * \brief
 * \param y Euler Angle rotation of y-axis
 */
void Matrix4x4::setRotationY(float y)
{
	const float y_rad = y * MathUtils::PI / 180.0f;
	this->setIdentity();
	this->matrix[0][0] = cos(y_rad);
	this->matrix[0][2] = -sin(y_rad);
	this->matrix[2][0] = sin(y_rad);
	this->matrix[2][2] = cos(y_rad);
}

/**
 * \brief
 * \param z Euler Angle rotation of z-axis
 */
void Matrix4x4::setRotationZ(float z)
{
	const float z_rad = z * MathUtils::PI / 180.0f;
	this->setIdentity();
	this->matrix[0][0] = cos(z_rad);
	this->matrix[0][1] = sin(z_rad);
	this->matrix[1][0] = -sin(z_rad);
	this->matrix[1][1] = cos(z_rad);
}

void Matrix4x4::setPerspectiveFovLH(float fov, float aspect, float znear, float zfar)
{
	this->setIdentity();
	float yscale = 1.0f / tan(fov / 2.0f);
	float xscale = yscale / aspect;
	this->matrix[0][0] = xscale;
	this->matrix[1][1] = yscale;
	this->matrix[2][2] = zfar / (zfar - znear);
	this->matrix[2][3] = 1.0f;
	this->matrix[3][2] = (-znear * zfar) / (zfar - znear);
}

void Matrix4x4::setOrthoLH(float width, float height, float near_plane, float far_plane)
{
	this->setIdentity();
	this->matrix[0][0] = 2.0f / width;
	this->matrix[1][1] = 2.0f / height;
	this->matrix[2][2] = 1.0f / (far_plane - near_plane);
	this->matrix[3][2] = -(near_plane / (far_plane - near_plane));
}

void Matrix4x4::setInverse()
{
	int a, i, j;
	Matrix4x4 out;
	Vector4D v, vec[3];
	float det = 0.0f;

	det = this->determinant();
	if (!det) return;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (j != i)
			{
				a = j;
				if (j > i) a = a - 1;
				vec[a].x = (this->matrix[j][0]);
				vec[a].y = (this->matrix[j][1]);
				vec[a].z = (this->matrix[j][2]);
				vec[a].w = (this->matrix[j][3]);
			}
		}
		v.cross(vec[0], vec[1], vec[2]);

		out.matrix[0][i] = pow(-1.0f, i) * v.x / det;
		out.matrix[1][i] = pow(-1.0f, i) * v.y / det;
		out.matrix[2][i] = pow(-1.0f, i) * v.z / det;
		out.matrix[3][i] = pow(-1.0f, i) * v.w / det;
	}

	this->setMatrix(out);
}


float Matrix4x4::determinant()
{
	Vector4D minor, v1, v2, v3;
	float det;

	v1 = Vector4D(this->matrix[0][0], this->matrix[1][0], this->matrix[2][0], this->matrix[3][0]);
	v2 = Vector4D(this->matrix[0][1], this->matrix[1][1], this->matrix[2][1], this->matrix[3][1]);
	v3 = Vector4D(this->matrix[0][2], this->matrix[1][2], this->matrix[2][2], this->matrix[3][2]);


	minor.cross(v1, v2, v3);
	det = -(this->matrix[0][3] * minor.getX() + this->matrix[1][3] * minor.getY() + this->matrix[2][3] * minor.getZ() +
		this->matrix[3][3] * minor.getW());
	return det;
}


Matrix4x4 Matrix4x4::multiplyTo(Matrix4x4 matrix)
{
	Matrix4x4 out;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			out.matrix[i][j] =
				this->matrix[i][0] * matrix.matrix[0][j] + this->matrix[i][1] * matrix.matrix[1][j] +
				this->matrix[i][2] * matrix.matrix[2][j] + this->matrix[i][3] * matrix.matrix[3][j];
		}
	}

	return out;
}

Vector3D Matrix4x4::getZDirection()
{
	return Vector3D(this->matrix[2][0], this->matrix[2][1], this->matrix[2][2]);
}

Vector3D Matrix4x4::getYDirection()
{
	return Vector3D(this->matrix[1][0], this->matrix[1][1], this->matrix[1][2]);
}

Vector3D Matrix4x4::getXDirection()
{
	return Vector3D(this->matrix[0][0], this->matrix[0][1], this->matrix[0][2]);
}


Vector3D Matrix4x4::getTranslation()
{
	return Vector3D(this->matrix[3][0], this->matrix[3][1], this->matrix[3][2]);
}

float* Matrix4x4::getMatrix()
{
	//re-arrange to be compatible with react physics
	return *this->matrix; // can be read as float [16]
}

void Matrix4x4::operator*=(const Matrix4x4& matrix)
{
	Matrix4x4 out;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			out.matrix[i][j] =
				this->matrix[i][0] * matrix.matrix[0][j] + this->matrix[i][1] * matrix.matrix[1][j] +
				this->matrix[i][2] * matrix.matrix[2][j] + this->matrix[i][3] * matrix.matrix[3][j];
		}
	}
	::memcpy(this->matrix, matrix.matrix, sizeof(float) * 16);
}

void Matrix4x4::debugPrint()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << this->matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
}

void Matrix4x4::matrixInitialize()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			this->matrix[i][j] = 0.0f;
		}
	}
}
