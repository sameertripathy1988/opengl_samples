#ifndef __TEXTURE_MAPING_H__
#define __TEXTURE_MAPING_H__

#include "BlankTest.h"

class TextureMaping : public BlankTest
{
public:
	TextureMaping();
	~TextureMaping();
	
	void InitScene();
	void RenderScene();
	
	GLuint indices[6];
	GLuint vbo;
	GLuint vao;
	HelperShader* texShader;
};

#endif 