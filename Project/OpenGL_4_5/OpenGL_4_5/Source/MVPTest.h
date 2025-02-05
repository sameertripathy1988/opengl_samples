#ifndef __MVP_TEST_H__
#define __MVP_TEST_H__

#include "BlankTest.h"

class MVPTest : public BlankTest
{
public:
	MVPTest();
	~MVPTest();
	
	void InitScene();
	void RenderScene();
	void UpdateScene();

	GLuint indices[6];
	GLuint vbo;
	GLuint vao;
	unique_ptr<HelperShader> texShader;
	GLuint texture;
};

#endif 