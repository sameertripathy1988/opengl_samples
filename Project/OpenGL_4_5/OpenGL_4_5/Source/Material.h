#pragma once
#include "glm\glm\glm.hpp"
#include "HelperShader.h"
#include <glew.h>

enum TEXTURE_TYPE
{
	DIFFUSE,
	NORMAL,
	DEPTH,
	TEXTURE_EXTRA
};

class Material
{
public:
	Material();
	~Material();
	void bind(shared_ptr<HelperShader> explicitShader = nullptr, float useDefaultShader = true);
	void unbind();
	
	void setShader(const shared_ptr<HelperShader>& shader_);
	void setTextureInfo(TEXTURE_TYPE textureType, const char* path);
	GLuint getTextureID(TEXTURE_TYPE textureType);

	void setColor(const glm::vec4& flat_color_);
	
	void linkMatrixToShader(const char* name, const GLfloat* value);
	void linkVec3ToShader(const char* name, GLfloat x, GLfloat y, GLfloat z);
	void linkIntToShader(const std::string& name, int value);
	glm::vec4 getColor();

	shared_ptr<HelperShader> shader;
	GLuint diffuse_map;
	GLuint normal_map;
	GLuint depth_map;
	GLuint texture_extra;
	
	glm::vec4 flat_color;
private:

};

