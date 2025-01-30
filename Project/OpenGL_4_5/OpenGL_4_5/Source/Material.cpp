#include "Material.h"
#include <Util.h>

Material::Material()
{
	diffuse_map = -1;
	normal_map = -1;
	depth_map = -1;
	texture_extra = -1;
	flat_color = glm::vec4(1.0, 1.0, 1.0, 1.0);
	shader = nullptr;
}

Material::~Material()
{
}

void Material::setShader(HelperShader* shader_)
{
	shader = shader_;
}

void Material::setTextureInfo(TEXTURE_TYPE textureType, const char* path)
{
	GLuint tex_id = Util::loadTexture(path);
	switch (textureType)
	{
		case DIFFUSE:
			diffuse_map = tex_id;
			break;
		case NORMAL:
			normal_map = tex_id;
			break;
		case DEPTH:
			depth_map = tex_id;
			break;
		case TEXTURE_EXTRA:
			texture_extra = tex_id;
			break;
		default:
			break;
	}
}

GLuint Material::getTextureID(TEXTURE_TYPE textureType)
{
	switch (textureType)
	{
		case DIFFUSE:
			return diffuse_map;
			break;
		case NORMAL:
			return normal_map;
			break;
		case DEPTH:
			return depth_map;
			break;
		case TEXTURE_EXTRA:
			return texture_extra;
			break;
		default:
			break;
	}
}

void Material::setColor(const glm::vec4& flat_color_)
{
	flat_color = flat_color_;
}

void Material::linkMatrixToShader(const char* matrix_name_shader, const GLfloat* value)
{
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), matrix_name_shader), 1, GL_FALSE, value);
}

void Material::linkVec3ToShader(const char* vec3_name_shader, GLfloat x, GLfloat y, GLfloat z)
{
	glUniform3f(glGetUniformLocation(shader->getProgramID(), vec3_name_shader), x, y, z);
}

void Material::apply()
{
	glUseProgram(shader->getProgramID());
}

glm::vec4 Material::getColor()
{
	return flat_color;
}

