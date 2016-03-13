#ifndef __TRIANGLE_TEST_H__
#define __TRIANGLE_TEST_H__

#include "BlankTest.h"

class TriangleTest : public BlankTest
{
public:
	TriangleTest();
	~TriangleTest();
	
	void InitScene();
	void RenderScene();

	GLuint vbo;
	GLuint vao;
	HelperShader* triangleShader;
};

#endif 