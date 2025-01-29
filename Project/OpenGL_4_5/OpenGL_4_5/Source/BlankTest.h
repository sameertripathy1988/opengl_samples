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
	virtual void UpdateInput(char x, int y, int z){ };
	virtual void UpdateMouseWheel(int wheel, int direction, int x, int y) { };
	virtual void UpdateMouseInput(int dx, int dy, bool bIsMouseLBDown) {};
	virtual void UpdateButtonUp(char x) {};
	virtual void clear() 
	{
		std::cout << "Clearing test name: " << name << std::endl;
	};
};

#endif