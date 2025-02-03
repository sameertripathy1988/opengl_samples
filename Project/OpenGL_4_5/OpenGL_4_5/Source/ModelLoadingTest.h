#ifndef __MODEL_LOADING_TEST_H__
#define __MODEL_LOADING_TEST_H__

#include "BlankTest.h"
#include "ThirdParty\SOIL.h"
#include "ThirdParty\tiny_obj_loader.h"

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
	MyMatrix* rotMatrix;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
};

#endif 