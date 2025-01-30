#include "MyCamera.h"
#include <glm/glm/gtc/matrix_transform.hpp> 

MyCamera::MyCamera() :
	position(glm::vec3(0, 0, 0)),
	fov(60.0f),
	width(CONFIG_WINDOW_WIDTH),
	height(CONFIG_WINDOW_HEIGHT),
	nearPlane(0.1f),
	farPlane(100.0f),
	isNoLockedTarget(false),
	lookAtTarget(glm::vec3(0,0,0))
{
	mat_perspectiveProj = glm::perspectiveFovRH(glm::radians(fov), width, height, nearPlane, farPlane);
	mat_View = glm::lookAtRH(position, lookAtTarget, glm::vec3(0, 1.0f, 0));
}

MyCamera::~MyCamera()
{

}

glm::mat4& MyCamera::getProjectionMatrix()
{
	return mat_perspectiveProj;
}

glm::mat4 & MyCamera::getViewMatrix()
{
	return mat_View;
}

glm::vec3& MyCamera::getPosition()
{
	return position;
}

void MyCamera::refreshViewMatrix()
{
	if(IsNoLockedTarget())
		setLookAt(getPosition() + glm::vec3(0, 0, -1.0f));
	mat_View = glm::lookAtRH(position, lookAtTarget, glm::vec3(0, 1.0f, 0));
}

void MyCamera::setPosition(const glm::vec3& _position)
{
	position = _position;
}

void MyCamera::setOffsetPosition(const glm::vec3&  _offset)
{
	position += _offset;
}

float& MyCamera::getFOV()
{
	return fov;
}

void MyCamera::setFOV(const float& _fov)
{
	this->fov = _fov;
	//Update the Projection Matrix too
	mat_perspectiveProj = glm::perspectiveFovRH(glm::radians(fov), width, height, nearPlane, farPlane);
}

void MyCamera::setLookAt(const glm::vec3 _targetPoint)
{
	lookAtTarget = _targetPoint;
}

glm::vec3& MyCamera::getLookAtPoint()
{
	return lookAtTarget;
}

