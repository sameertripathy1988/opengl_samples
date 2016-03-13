#ifndef __SPECULAR_LIGHTING_TEST_H__
#define __SPECULAR_LIGHTING_TEST_H__

#include "BlankTest.h"
#include "glm\glm\glm.hpp"

class SpecularLightingTest : public BlankTest
{
public:
	SpecularLightingTest();
	~SpecularLightingTest();
	
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
	static float diffuseStrength;
	glm::vec3 light_pos;
	glm::vec3 eye_pos;
	glm::vec3 target_pos;
	bool isLightMovementOn;
	float shineness;
};

#endif 