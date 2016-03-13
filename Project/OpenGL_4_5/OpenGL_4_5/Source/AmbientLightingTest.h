#ifndef __AMBIENT_LIGHTING_TEST_H__
#define __AMBIENT_LIGHTING_TEST_H__

#include "BlankTest.h"
#include "glm\glm\glm.hpp"

class AmbientLightingTest : public BlankTest
{
public:
	AmbientLightingTest();
	~AmbientLightingTest();
	
	void InitScene();
	void RenderScene();
	void UpdateInput(int x, int y, int z);

	GLuint vbo;
	GLuint vao;
	HelperShader* triangleShader;
	glm::vec3 lightColor;
	static float ambientStrength;
	glm::vec3 eye_pos;
};

#endif 