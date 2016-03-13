#ifndef __GEOMETRY_SHADER_CIRCLE_TEST_H__
#define __GEOMETRY_SHADER_CIRCLE_TEST_H__

#include "BlankTest.h"

class GeometryShaderCircleTest : public BlankTest
{
public:
	GeometryShaderCircleTest();
	~GeometryShaderCircleTest();
	
	void InitScene();
	void RenderScene();

	GLuint vbo;
	GLuint vao;
	HelperShader* triangleShader;
};

#endif 