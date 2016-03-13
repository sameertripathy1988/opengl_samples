#include "MathHelper.h"

MathHelper* MathHelper::instance = 0;

MathHelper::MathHelper()
{

}

MathHelper::~MathHelper()
{

}

MathHelper* MathHelper::getInstance()
{
	if (instance == 0)
		instance = new MathHelper();
	return instance;
}

MyMatrix::MyMatrix()
{
	setIdentity();
}

void MyMatrix::setIdentity()
{
	arr[0][0] = 1;
	arr[0][1] = 0;
	arr[0][2] = 0;
	arr[0][3] = 0;

	arr[1][0] = 0;
	arr[1][1] = 1;
	arr[1][2] = 0;
	arr[1][3] = 0;

	arr[2][0] = 0;
	arr[2][1] = 0;
	arr[2][2] = 1;
	arr[2][3] = 0;

	arr[3][0] = 0;
	arr[3][1] = 0;
	arr[3][2] = 0;
	arr[3][3] = 1;
}

MyMatrix::MyMatrix(float _11, float _12, float _13, float _14,
	float _21, float _22, float _23, float _24,
	float _31, float _32, float _33, float _34,
	float _41, float _42, float _43, float _44)
{
	arr[0][0] = _11;
	arr[0][1] = _12;
	arr[0][2] = _13;
	arr[0][3] = _14;

	arr[1][0] = _21;
	arr[1][1] = _22;
	arr[1][2] = _23;
	arr[1][3] = _24;

	arr[2][0] = _31;
	arr[2][1] = _32;
	arr[2][2] = _33;
	arr[2][3] = _34;

	arr[3][0] = _41;
	arr[3][1] = _42;
	arr[3][2] = _43;
	arr[3][3] = _44;
}

void MyMatrix::scalarMultiplication(float a)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			arr[i][j] *= a;
		}
	}
}

MyMatrix MyMatrix::operator*(MyMatrix& a)
{
	return *(multiplyMatrix(&a));
}

Vector MyMatrix::operator*(Vector& a)
{
	Vector result;
	result.x = (this->arr[0][0] * a.x) + (this->arr[0][1] * a.y) + (this->arr[0][2] * a.z) + (this->arr[0][3] * a.w);
	result.y = (this->arr[1][0] * a.x) + (this->arr[1][1] * a.y) + (this->arr[1][2] * a.z) + (this->arr[1][3] * a.w);
	result.z = (this->arr[2][0] * a.x) + (this->arr[2][1] * a.y) + (this->arr[2][2] * a.z) + (this->arr[2][3] * a.w);
	result.w = (this->arr[3][0] * a.x) + (this->arr[3][1] * a.y) + (this->arr[3][2] * a.z) + (this->arr[3][3] * a.w);
	return result;
}

MyMatrix* MyMatrix::multiplyMatrix(MyMatrix* a)
{
	MyMatrix* result = new MyMatrix();
	result->arr[0][0] = (this->arr[0][0] * a->arr[0][0]) + (this->arr[0][1] * a->arr[1][0]) + (this->arr[0][2] * a->arr[2][0]) + (this->arr[0][3] * a->arr[3][0]);
	result->arr[0][1] = (this->arr[0][0] * a->arr[0][1]) + (this->arr[0][1] * a->arr[1][1]) + (this->arr[0][2] * a->arr[2][1]) + (this->arr[0][3] * a->arr[3][1]);
	result->arr[0][2] = (this->arr[0][0] * a->arr[0][2]) + (this->arr[0][1] * a->arr[1][2]) + (this->arr[0][2] * a->arr[2][2]) + (this->arr[0][3] * a->arr[3][2]);
	result->arr[0][3] = (this->arr[0][0] * a->arr[0][3]) + (this->arr[0][1] * a->arr[1][3]) + (this->arr[0][2] * a->arr[2][3]) + (this->arr[0][3] * a->arr[3][3]);

	result->arr[1][0] = (this->arr[1][0] * a->arr[0][0]) + (this->arr[1][1] * a->arr[1][0]) + (this->arr[1][2] * a->arr[2][0]) + (this->arr[1][3] * a->arr[3][0]);
	result->arr[1][1] = (this->arr[1][0] * a->arr[0][1]) + (this->arr[1][1] * a->arr[1][1]) + (this->arr[1][2] * a->arr[2][1]) + (this->arr[1][3] * a->arr[3][1]);
	result->arr[1][2] = (this->arr[1][0] * a->arr[0][2]) + (this->arr[1][1] * a->arr[1][2]) + (this->arr[1][2] * a->arr[2][2]) + (this->arr[1][3] * a->arr[3][2]);
	result->arr[1][3] = (this->arr[1][0] * a->arr[0][3]) + (this->arr[1][1] * a->arr[1][3]) + (this->arr[1][2] * a->arr[2][3]) + (this->arr[1][3] * a->arr[3][3]);

	result->arr[2][0] = (this->arr[2][0] * a->arr[0][0]) + (this->arr[2][1] * a->arr[1][0]) + (this->arr[2][2] * a->arr[2][0]) + (this->arr[2][3] * a->arr[3][0]);
	result->arr[2][1] = (this->arr[2][0] * a->arr[0][1]) + (this->arr[2][1] * a->arr[1][1]) + (this->arr[2][2] * a->arr[2][1]) + (this->arr[2][3] * a->arr[3][1]);
	result->arr[2][2] = (this->arr[2][0] * a->arr[0][2]) + (this->arr[2][1] * a->arr[1][2]) + (this->arr[2][2] * a->arr[2][2]) + (this->arr[2][3] * a->arr[3][2]);
	result->arr[2][3] = (this->arr[2][0] * a->arr[0][3]) + (this->arr[2][1] * a->arr[1][3]) + (this->arr[2][2] * a->arr[2][3]) + (this->arr[2][3] * a->arr[3][3]);

	result->arr[3][0] = (this->arr[3][0] * a->arr[0][0]) + (this->arr[3][1] * a->arr[1][0]) + (this->arr[3][2] * a->arr[2][0]) + (this->arr[3][3] * a->arr[3][0]);
	result->arr[3][1] = (this->arr[3][0] * a->arr[0][1]) + (this->arr[3][1] * a->arr[1][1]) + (this->arr[3][2] * a->arr[2][1]) + (this->arr[3][3] * a->arr[3][1]);
	result->arr[3][2] = (this->arr[3][0] * a->arr[0][2]) + (this->arr[3][1] * a->arr[1][2]) + (this->arr[3][2] * a->arr[2][2]) + (this->arr[3][3] * a->arr[3][2]);
	result->arr[3][3] = (this->arr[3][0] * a->arr[0][3]) + (this->arr[3][1] * a->arr[1][3]) + (this->arr[3][2] * a->arr[2][3]) + (this->arr[3][3] * a->arr[3][3]);
	return result;
}

void MyMatrix::translateMatrix(float x, float y, float z)
{
	this->arr[0][3] = x;
	this->arr[1][3] = y;
	this->arr[2][3] = z;
}

void MyMatrix::scaleMatrix(float x, float y, float z)
{
	this->arr[0][0] = x;
	this->arr[1][1] = y;
	this->arr[2][2] = z;
}

void MyMatrix::rotateMatrixAboutX(float alpha)
{
	this->arr[1][1] = cosf(alpha);
	this->arr[1][2] = -sinf(alpha);
	this->arr[2][1] = sinf(alpha);
	this->arr[2][2] = cosf(alpha);
}

void MyMatrix::rotateMatrixAboutY(float beta)
{
	beta = TORADIAN(beta);
	this->arr[0][0] = cosf(beta);
	this->arr[0][2] = -sinf(beta);
	this->arr[2][0] = sinf(beta);
	this->arr[2][2] = cosf(beta);
}

void MyMatrix::rotateMatrixAboutZ(float gamma)
{

	this->arr[0][0] = cosf(gamma);
	this->arr[0][1] = -sinf(gamma);
	this->arr[1][0] = sinf(gamma);
	this->arr[1][1] = cosf(gamma);
}

void MyMatrix::constructCameraRotationMatrix(Vector forward, Vector right, Vector up, Vector camPos)
{
	
}

void MyMatrix::lookAt(Vector camPos, Vector targetPos, Vector upVector)
{
	//Basically this is look-at vector
	//But our 3rd row is Forward vector which is opposite to the look-at vector so it is -F

	//1. Translate the point w.r.t camp pos. Thus Cam pos is our new origin.
	//Translation matrix for a point to move into camera space is just a translation matrix with -Cx, -Cy, -Cz

	//2. Then multiply with the change of basis matrix constructed by R,U,F to change the coordinate system of the point w.r.t the new camera space orthonormal basis vectors.
	
	Vector F =  Vector::normalize( targetPos - camPos );

	Vector R = Vector::cross(F, upVector);
	Vector U = Vector::cross(R, F);
	
	//Right Vector
	this->arr[0][0] = R.x;
	this->arr[0][1] = R.y;
	this->arr[0][2] = R.z;
	this->arr[0][3] = -Vector::dot(R, camPos);

	//Up Vector
	this->arr[1][0] = U.x;
	this->arr[1][1] = U.y;
	this->arr[1][2] = U.z;
	this->arr[1][3] = -Vector::dot(U, camPos);

	//Forward Vector
	this->arr[2][0] = -F.x;
	this->arr[2][1] = -F.y;
	this->arr[2][2] = -F.z;
	this->arr[2][3] = Vector::dot(F, camPos);

	this->arr[3][0] = 0;
	this->arr[3][1] = 0;
	this->arr[3][2] = 0;
	this->arr[3][3] = 1;
}

void MyMatrix::createPerspectiveProjectionMatrix(float fov, float screenWidth, float screenHeight, float near, float far )
{
	//Near plane will be clamped to -1 and Far plane will be clamped to +1
	//Then by considering a and b as the 2,2 and 2,3 position in the matrix we can calculated the value of a and b.
	//0,0 will be 1/ar*tan(halfFOV) and 1,1 will be 1/tan(halfFOV)
	//This will result in a pyramidal shape of frustum where the point will be visible inside the frustum and will be culled outside it.

	const float aspectRatio = screenWidth / screenHeight;
	const float tanofhalfFOV = tanf( TORADIAN(fov / 2) );
	const float zRange = far - near;


	this->arr[0][0] = 1.0f / (aspectRatio * tanofhalfFOV); //X component
	this->arr[1][1] = 1.0f / tanofhalfFOV; //Y component 
	this->arr[2][2] = -(far + near) / zRange;
	this->arr[2][3] = -( 2.0f *far * near ) / zRange;
	this->arr[3][2] = -1.0f;
	this->arr[3][3] = 0.0f;
}