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
	lookAtTarget(glm::vec3(0,0,0)),
    yaw(-90.0f),
    pitch(0.0f),
    movementSpeed(2.5f),
    mouseSensitivity(0.1f),
    worldUp(glm::vec3(0.0f, 1.0f, 0.0f))
{
    updateCameraVectors();
	mat_perspectiveProj = glm::perspectiveFovRH(glm::radians(fov), width, height, nearPlane, farPlane);
	mat_View = glm::lookAtRH(position, lookAtTarget, up);
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
	/*if(IsNoLockedTarget())
		setLookAt(getPosition() + glm::vec3(0, 0, -1.0f));*/

    lookAtTarget = position + front;
    mat_View = glm::lookAtRH(position, lookAtTarget, up);
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

void MyCamera::processMouseMovement(float xoffset, float yoffset) {
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // Constrain the pitch
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    // Update front, right, and up vectors
    updateCameraVectors();
}

void MyCamera::processKeyboardMovement(const glm::vec3& direction, float deltaTime) {
    float velocity = movementSpeed * deltaTime;
    if (direction.z != 0.0f)
        position += front * direction.z * velocity;
    if (direction.x != 0.0f)
        position += right * direction.x * velocity;
    if (direction.y != 0.0f)
        position += up * direction.y * velocity;
    refreshViewMatrix();
}

void MyCamera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->front = glm::normalize(front);
    right = glm::normalize(glm::cross(this->front, worldUp));
    up = glm::normalize(glm::cross(right, this->front));
    refreshViewMatrix();
}