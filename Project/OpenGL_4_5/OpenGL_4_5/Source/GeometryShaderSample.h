#ifndef __GEOMETRY_SHADER_SAMPLE_H__
#define __GEOMETRY_SHADER_SAMPLE_H__

#include "BlankTest.h"

class GeometryShaderSample : public BlankTest
{
public:
	GeometryShaderSample();
	~GeometryShaderSample();
	
	void InitScene();
	void RenderScene();

	GLuint vbo;
	GLuint vao;
	HelperShader* triangleShader;
};

#endif 