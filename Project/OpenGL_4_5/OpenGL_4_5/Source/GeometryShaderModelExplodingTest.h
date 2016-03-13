#ifndef __GEOMETRY_SHADER_MODEL_EXPLODING_TEST_H__
#define __GEOMETRY_SHADER_MODEL_EXPLODING_TEST_H__


#include "BlankTest.h"
#include "ThirdParty\tiny_obj_loader.h"


class GeometryShaderModelExplodingTest : public BlankTest
{
public:
	GeometryShaderModelExplodingTest();
	~GeometryShaderModelExplodingTest();

	void InitScene();
	void RenderScene();
	void UpdateScene();

	GLuint indices[6];
	GLuint vbo;
	GLuint vao;
	HelperShader* texShader;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	GLuint uvBuffer;
	float counter;
	float angle;

};

#endif 