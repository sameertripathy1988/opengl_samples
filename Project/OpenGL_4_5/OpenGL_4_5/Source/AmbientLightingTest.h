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
	void UpdateInput(char x, int y, int z);
	void UpdateButtonUp(char x);
	void UpdateMouseWheel(int wheel, int direction, int x, int y);
	void UpdateMouseInput(int dx, int dy, bool bIsMouseLBDown);
	GLuint vbo;
	GLuint vao;
	HelperShader* triangleShader;
	glm::vec3 lightColor;
	static float ambientStrength;
	glm::vec3 eye_pos;
	MyCamera* mainCamera;
};

#endif 