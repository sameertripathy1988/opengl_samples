#ifndef __HELPER_SHADER_H__
#define __HELPER_SHADER_H__

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
class HelperShader
{

public:
	HelperShader();
	~HelperShader();
	int getProgramID();
	int createProgram(const char* vertexShaderFile, const char* fragShaderFile, const char* geomShaderFile = NULL, const char* tesControlShader = NULL,
		const char* tesEvalutaionShader = NULL);

private:
	int program;
	std::string loadFile(const char *fname);

};

#endif