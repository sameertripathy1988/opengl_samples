#ifndef __DIFFUSE_LIGHTING_TEST_H__
#define __DIFFUSE_LIGHTING_TEST_H__

#include "BlankTest.h"
#include "glm\glm\glm.hpp"
#include "MyCamera.h"

class DiffuseLightingTest : public BlankTest
{
public:
	DiffuseLightingTest();
	~DiffuseLightingTest();
	
	void InitScene();
	void RenderScene();
	void UpdateScene();
	void UpdateMouseWheel(int wheel, int direction, int x, int y);
	void UpdateInput(int x, int y, int z);
	void UpdateCameraOnInput(int x);
	GLuint vbo;
	GLuint vao;
	GLuint lampvao;
	
	shared_ptr<HelperShader> diffuseShader;
	shared_ptr<HelperShader> lampShader;

	glm::vec3 lightColor;
	static float ambientStrength;
	glm::vec3 light_pos;
	glm::vec3 eye_pos;
	glm::vec3 target_pos;
	bool isLightMovementOn;
	unique_ptr<MyCamera> mainCamera;
	GLuint texture;
};

#endif 