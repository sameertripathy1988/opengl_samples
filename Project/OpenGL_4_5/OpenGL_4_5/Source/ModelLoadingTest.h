#ifndef __MODEL_LOADING_TEST_H__
#define __MODEL_LOADING_TEST_H__

#include "BlankTest.h"

class ModelLoadingTest : public BlankTest
{
public:
	ModelLoadingTest();
	~ModelLoadingTest();
	
	void InitScene();
	void RenderScene();
	void UpdateScene();

	GLuint indices[6];
	GLuint vbo;
	GLuint vao;
	HelperShader* texShader;
};

#endif 