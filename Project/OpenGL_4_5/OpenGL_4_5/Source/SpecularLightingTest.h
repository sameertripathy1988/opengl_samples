#ifndef __SPECULAR_LIGHTING_TEST_H__
#define __SPECULAR_LIGHTING_TEST_H__

#include "BlankTest.h"
#include "glm\glm\glm.hpp"
#include "MyCamera.h"

class SpecularLightingTest : public BlankTest
{
public:
	SpecularLightingTest();
	~SpecularLightingTest();
	
	void InitScene();
	void RenderScene();
	void UpdateScene();
	void UpdateMouseWheel(int wheel, int direction, int x, int y);
	void UpdateInput(int x, int y, int z);
	void UpdateCameraOnInput(int x);

	GLuint vbo;
	GLuint vao;
	GLuint lampvao;
	HelperShader* diffuseShader;
	HelperShader* lampShader;
	glm::vec3 lightColor;
	static float ambientStrength;
	static float diffuseStrength;
	glm::vec3 light_pos;
	glm::vec3 eye_pos;
	glm::vec3 target_pos;
	bool isLightMovementOn;
	float shineness;
	MyCamera* mainCamera;

};

#endif 