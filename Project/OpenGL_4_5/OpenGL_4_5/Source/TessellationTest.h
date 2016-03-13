#ifndef __TESSELLATION_TEST_H__
#define __TESSELLATION_TEST_H__

#include "BlankTest.h"

class TessellationTest : public BlankTest
{
public:
	TessellationTest();
	~TessellationTest();
	
	void InitScene();
	void RenderScene();

	GLuint vbo;
	GLuint vao;
	HelperShader* triangleShader;
};

#endif 