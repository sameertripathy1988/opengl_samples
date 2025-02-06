#pragma once

#include "glew.h"
#include <iostream>
#include "freeglut.h"
class Util
{
public:
	Util();
	~Util();
	 static int loadTexture(const std::string& path);
	 static float delta_time;
private:

};