#ifndef __MATH_HELPER_H__
#define __MATH_HELPER_H__

#include "glew.h"
#include <iostream>

#define MATH_PI 3.142f
#define TORADIAN(X) (X * MATH_PI)/180.0f 



struct Vector
{
	float x;
	float y;
	float z;
	float w;

	Vector()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 1;
	}

	Vector(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
		w = 1;
	}

	Vector(float _x, float _y, float _z, float _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}


	Vector operator+(const Vector& other)
	{
		return Vector(x + other.x, y + other.y, z + other.z);
	}

	Vector operator-(const Vector& other)
	{
		return Vector(x - other.x, y - other.y, z - other.z);
	}

	Vector static normalize(Vector a)
	{
		float length = sqrtf( dot(a, a));
		return Vector(a.x/length, a.y/length, a.z/ length);
	}

	float static dot(Vector a, Vector b)
	{
		return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
	}

	Vector static cross(Vector a, Vector b)
	{
		float tempX = a.y * b.z - a.z * b.y;
		float tempY = a.z * b.x - a.x * b.z;
		float tempZ = a.x * b.y - a.y * b.x;

		return Vector(tempX,tempY,tempZ);
	}
};


class MyMatrix
{
	
public:
	GLfloat arr[4][4];

	MyMatrix(); //Identity Matrix
	MyMatrix(float _11, float _12, float _13, float _14,
							float _21, float _22, float _23, float _24,
							float _31, float _32, float _33, float _34,
							float _41, float _42, float _43, float _44);
	void setIdentity();
	MyMatrix operator*(MyMatrix& a);
	Vector operator*(Vector& a);
	MyMatrix* multiplyMatrix(MyMatrix* a);
	void scalarMultiplication(float a);
	void translateMatrix(float x, float y, float z);
	void scaleMatrix(float x, float y, float z);

	void rotateMatrixAboutX(float alpha);
	void rotateMatrixAboutY(float beta);
	void rotateMatrixAboutZ(float gamma);

	void constructCameraRotationMatrix(Vector u, Vector v, Vector w, Vector camPos);
	void createPerspectiveProjectionMatrix(float fov, float screenWidth, float screenHeight, float near, float far);
	void lookAt(Vector camPos, Vector targetPos, Vector upVector);
};

class MathHelper
{
public:
	MathHelper();
	~MathHelper();
	static MathHelper* getInstance();
	
private:
	static MathHelper* instance;
};


struct Quaternion
{
	float q[4];

	Quaternion()
	{
		q[0] = q[1] = q[2] = q[3] = 0;
	}

	Quaternion(float w, float x, float y, float z)
	{
		q[0] = w;
		q[1] = x;
		q[2] = y;
		q[3] = z;
	}

	Quaternion conjugate()
	{
		return Quaternion(q[0], -q[1], -q[2], -q[3]);
	}

	Quaternion static normalize(Quaternion quat)
	{
		int squaredValue = (quat.q[0] * quat.q[0]) + (quat.q[1] * quat.q[1]) + (quat.q[2] * quat.q[2]) + (quat.q[3] * quat.q[3]);
		float squaredRoot = float(sqrt(squaredValue));
		return Quaternion(quat.q[0] / squaredRoot, quat.q[1] / squaredRoot, quat.q[2] / squaredRoot, quat.q[3] / squaredRoot);
	}

	void createMatrix(MyMatrix* pMatrix)
	{
		if (pMatrix)
		{
			// First row
			pMatrix->arr[0][0] = 1.0f - 2.0f * (q[2] * q[2] + q[3] * q[3]);
			pMatrix->arr[0][1] = 2.0f * (q[1] * q[2] - q[0] * q[3]);
			pMatrix->arr[0][2] = 2.0f * (q[1] * q[3] + q[0] * q[2]);
			pMatrix->arr[0][3] = 0.0f;

			// Second row
			pMatrix->arr[1][0] = 2.0f * (q[1] * q[2] + q[0] * q[3]);
			pMatrix->arr[1][1] = 1.0f - 2.0f * (q[1] * q[1] + q[3] * q[3]);
			pMatrix->arr[1][2] = 2.0f * (q[2] * q[3] - q[0] * q[1]);
			pMatrix->arr[1][3] = 0.0f;

			// Third row
			pMatrix->arr[2][0] = 2.0f * (q[1] * q[3] - q[0] * q[2]);
			pMatrix->arr[2][1] = 2.0f * (q[2] * q[3] + q[0] * q[1]);
			pMatrix->arr[2][2] = 1.0f - 2.0f * (q[1] * q[1] + q[2] * q[2]);
			pMatrix->arr[2][3] = 0.0f;

			// Fourth row
			pMatrix->arr[3][0] = 0;
			pMatrix->arr[3][1] = 0;
			pMatrix->arr[3][2] = 0;
			pMatrix->arr[3][3] = 1.0f;
		}
	}

	Quaternion operator*(Quaternion &quat)
	{
		Quaternion r;

		r.q[0] = q[0] * quat.q[0] - q[1] * quat.q[1] - q[2] * quat.q[2] - q[3] * quat.q[3];
		r.q[1] = q[0] * quat.q[1] + q[1] * quat.q[0] + q[2] * quat.q[3] - q[3] * quat.q[2];
		r.q[2] = q[0] * quat.q[2] + q[2] * quat.q[0] + q[3] * quat.q[1] - q[1] * quat.q[3];
		r.q[3] = q[0] * quat.q[3] + q[3] * quat.q[0] + q[1] * quat.q[2] - q[2] * quat.q[1];

		return r;
	}
	void CreateFromAxisAngle(const float &in_x, const float &in_y, const float &in_z, const float &in_degrees)
	{

		float halfAngle = float(TORADIAN(in_degrees)) / 2;
		float result = float(sin(halfAngle));
		q[0] = float(cos(halfAngle));

		// Calculate the x, y and z of the quaternion
		q[1] = float(in_x * result);
		q[2] = float(in_y * result);
		q[3] = float(in_z * result);
	}
};

#endif