#ifndef __DIFFUSE_LIGHTING_TEST_H__
#define __DIFFUSE_LIGHTING_TEST_H__

#include "BlankTest.h"
#include "glm\glm\glm.hpp"

class DiffuseLightingTest : public BlankTest
{
public:
	DiffuseLightingTest();
	~DiffuseLightingTest();
	
	void InitScene();
	void RenderScene();
	void UpdateInput(int x, int y, int z);

	GLuint vbo;
	GLuint vao;
	GLuint lampvao;
	HelperShader* diffuseShader;
	HelperShader* lampShader;
	glm::vec3 lightColor;
	static float ambientStrength;
	glm::vec3 light_pos;
	glm::vec3 eye_pos;
	glm::vec3 target_pos;
	bool isLightMovementOn;
};

#endif 