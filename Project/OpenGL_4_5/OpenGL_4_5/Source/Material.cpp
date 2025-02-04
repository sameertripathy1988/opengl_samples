#include "Material.h"
#include <Util.h>

Material::Material() : shader(0), diffuse_map(0), normal_map(0), depth_map(0), texture_extra(0), 
flat_color(glm::vec4(1.0, 1.0, 1.0, 1.0))
{
}

Material::~Material()
{
	if (diffuse_map)
	{
		glDeleteTextures(1, &diffuse_map);
	}
	if (normal_map)
	{
		glDeleteTextures(1, &normal_map);
	}
	if (depth_map)
	{
		glDeleteTextures(1, &depth_map);
	}
	if (texture_extra)
	{
		glDeleteTextures(1, &texture_extra);
	}
}

void Material::bind(shared_ptr<HelperShader> explicitShader, float useDefaultShader)
{
	shared_ptr<HelperShader> currentShader;

	if (useDefaultShader)
	{
		currentShader = shader;
	}
	else
	{
		currentShader = explicitShader;
	}

	if (currentShader)
	{
		glUseProgram(currentShader->getProgramID());
		if (diffuse_map)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, diffuse_map);
			glUniform1i(glGetUniformLocation(currentShader->getProgramID(), "diffuse_map"), 0);
		}
		if (normal_map)
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, normal_map);
			glUniform1i(glGetUniformLocation(currentShader->getProgramID(), "normal_map"), 1);
		}
		if (depth_map)
		{
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, depth_map);
			glUniform1i(glGetUniformLocation(currentShader->getProgramID(), "depth_map"), 2);
		}
		if (texture_extra)
		{
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, texture_extra);
			glUniform1i(glGetUniformLocation(currentShader->getProgramID(), "texture_extra"), 3);
		}
	}
}


void Material::unbind()
{
	glUseProgram(0);
}

void Material::setShader(const shared_ptr<HelperShader>& shader_)
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

void Material::linkMatrixToShader(const char* name, const GLfloat* value)
{
	shader->setMat4(name, value);
}

void Material::linkVec3ToShader(const char* name, GLfloat x, GLfloat y, GLfloat z)
{
	shader->setVec3(name, x, y, z);
}
void Material::linkIntToShader(const std::string& name, int value)
{
	shader->setInt(name, value);
}

glm::vec4 Material::getColor()
{
	return flat_color;
}