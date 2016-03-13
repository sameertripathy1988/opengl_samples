#ifndef __COLORED_TRIANGLE_TEST_H__
#define __COLORED_TRIANGLE_TEST_H__

#include "BlankTest.h"

class ColoredTriangle : public BlankTest
{
public:
	ColoredTriangle();
	~ColoredTriangle();
	
	void InitScene();
	void RenderScene();

	GLuint vbo;
	GLuint vao;
	HelperShader* colTriangleShader;
};

#endif 