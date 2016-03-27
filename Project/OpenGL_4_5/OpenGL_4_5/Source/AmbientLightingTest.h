#ifndef __AMBIENT_LIGHTING_TEST_H__
#define __AMBIENT_LIGHTING_TEST_H__

#include "BlankTest.h"
#include "glm\glm\glm.hpp"
#include "MyCamera.h"

class AmbientLightingTest : public BlankTest
{
public:
	AmbientLightingTest();
	~AmbientLightingTest();
	
	void InitScene();
	void RenderScene();
	void UpdateScene();
	void UpdateInput(int x, int y, int z);
	void UpdateCameraOnInput(int x);
	void UpdateMouseWheel(int wheel, int direction, int x, int y);

	GLuint vbo;
	GLuint vao;
	HelperShader* triangleShader;
	glm::vec3 lightColor;
	static float ambientStrength;
	glm::vec3 eye_pos;
	MyCamera* mainCamera;
};

#endif 