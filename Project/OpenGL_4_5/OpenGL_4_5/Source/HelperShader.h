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

    void use();
    void setMat4(const std::string& name, const float* matrix);
	void setVec3(const std::string& name, float x, float y, float z);
	void setInt(const std::string& name, int value);
	void setTexture(const std::string& name, int tex_id, int textureUnit);

private:
	int program;
	std::string loadFile(const char *fname);

};

#endif