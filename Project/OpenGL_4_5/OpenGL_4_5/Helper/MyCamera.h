#pragma once
#include <glm/glm/gtc/matrix_transform.hpp>
#include "Config.h"

class MyCamera
{
public:
	MyCamera();
	~MyCamera();
	glm::mat4& getProjectionMatrix();
	glm::mat4& getViewMatrix();
	glm::vec3& getPosition();
	void refreshViewMatrix();
	void setPosition(glm::vec3& _position);
	void setOffsetPosition(glm::vec3& _offset);
	float& getFOV();
	void setFOV(const float& _fov);
	void setLookAt(const glm::vec3& _targetPoint);
	glm::vec3& getLookAtPoint();
	bool IsNoLockedTarget() const { return isNoLockedTarget; }
	void SetIsNoLockedTarget(bool val) { isNoLockedTarget = val; }
private:
	glm::vec3 position;
	glm::vec3 lookAtTarget;
	float fov;
	float width;
	float height;
	float nearPlane;
	float farPlane;
	glm::mat4 mat_perspectiveProj;
	glm::mat4 mat_View;
	bool isNoLockedTarget;
};