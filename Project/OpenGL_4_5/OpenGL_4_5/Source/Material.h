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
	void bind();
	void unbind();
	
	void setShader(const shared_ptr<HelperShader>& shader_);
	void setTextureInfo(TEXTURE_TYPE textureType, const char* path);
	GLuint getTextureID(TEXTURE_TYPE textureType);

	void setColor(const glm::vec4& flat_color_);
	
	void linkMatrixToShader(const char* matrix_name_shader, const GLfloat* value);
	void linkVec3ToShader(const char* vec3_name_shader, GLfloat x, GLfloat y, GLfloat z);

	glm::vec4 getColor();

	shared_ptr<HelperShader> shader;
	GLuint diffuse_map;
	GLuint normal_map;
	GLuint depth_map;
	GLuint texture_extra;
	
	glm::vec4 flat_color;
private:

};

