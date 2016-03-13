#ifndef __BLANK_TEST_H__
#define __BLANK_TEST_H__

#include "glew.h"
#include "HelperShader.h"
#include "MathHelper.h"

class BlankTest
{
public:
	BlankTest(){}
	~BlankTest(){}
	const char* name = "Blank Test";
	virtual void InitScene() = 0;
	virtual void RenderScene() = 0;
	virtual void UpdateScene(){};
	virtual void UpdateInput(int x, int y, int z){ };
};

#endif