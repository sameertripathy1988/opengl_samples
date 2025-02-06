#include "MeshRenderer.h"
#include "GeometryData.h"

MeshRenderer::MeshRenderer() : material(nullptr), model_vbo(0), model_vao(0), ebo(0),
meshType(PLANE), translation(0.0f), rotation(0.0f), scale(1.0f)
{
}

MeshRenderer::~MeshRenderer()
{
	if (model_vbo)  glDeleteBuffers(1, &model_vbo);
	if (model_vao)  glDeleteVertexArrays(1, &model_vao);
	if (ebo)  glDeleteBuffers(1, &ebo);
}

void MeshRenderer::render()
{
	switch (meshType)
	{
	case PLANE:
		renderPlane();
		break;
	case CUBE:
		renderCube();
		break;
	case MODEL:
		renderModel();
		break;
	case LINE:
		renderLine();
		break;
	default:
		break;
	}
}

void MeshRenderer::create(const MESH_TYPE& meshType_)
{
	meshType = meshType_;
	switch (meshType)
	{
		case PLANE:
			createPlane();
			break;
		case CUBE:
			createCube();
			break;
		case MODEL:
			createModel();
			break;
		case LINE:
			createLine();
			break;
		default:
			break;
	}
}

void MeshRenderer::setMaterial(const shared_ptr<Material>& material_)
{
	material = material_;
}

void MeshRenderer::createPlane()
{
	
	glGenVertexArrays(1, &model_vao);
	glBindVertexArray(model_vao);

	glGenBuffers(1, &model_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, model_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(plane_pos_uv_n_t_b), plane_pos_uv_n_t_b, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(planeIndices), planeIndices, GL_STATIC_DRAW);

	GLsizei stride = 14 * sizeof(GLfloat);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(8 * sizeof(GLfloat)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(11 * sizeof(GLfloat)));
	glEnableVertexAttribArray(4);

}

void MeshRenderer::createCube()
{
	glGenBuffers(1, &model_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, model_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_pos_uv_n), cube_pos_uv_n, GL_STATIC_DRAW);

	glGenVertexArrays(1, &model_vao);
	glBindVertexArray(model_vao);

	GLsizei stride = 8 * sizeof(GLfloat);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)0); // Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(3 * sizeof(GLfloat))); // UV
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(5 * sizeof(GLfloat))); // Normal
	glEnableVertexAttribArray(2);
}

void MeshRenderer::createModel()
{
}

void MeshRenderer::createLine()
{
	float lineVertices[] = {
		point1.x, point1.y, point1.z,  // Point A (x, y, z)
		 point2.x,  point2.y, point2.z   // Point B (x, y, z)
	};

	glGenVertexArrays(1, &model_vao);
	glGenBuffers(1, &model_vbo);

	glBindVertexArray(model_vao);

	glBindBuffer(GL_ARRAY_BUFFER, model_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void MeshRenderer::renderPlane()
{
	glBindVertexArray(model_vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void MeshRenderer::renderCube()
{
	glBindVertexArray(model_vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void MeshRenderer::renderModel()
{
}
void MeshRenderer::renderLine()
{
	glBindVertexArray(model_vao);
	glLineWidth(lineWidth);
	glDrawArrays(GL_LINES, 0, 2);
}
void MeshRenderer::render(shared_ptr<HelperShader> shader)
{
	switch (meshType)
	{
	case PLANE:
		{
			shader->use();
			glBindVertexArray(model_vao);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
		break;
	case CUBE:
		{
			shader->use();
			glBindVertexArray(model_vao);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		break;
	case MODEL:
		break;
	default:
		break;
	}
}
// Setters and getters for transformation variables
void MeshRenderer::setTranslation(const glm::vec3& translation_)
{
	translation = translation_;
}

glm::vec3 MeshRenderer::getTranslation() const
{
	return translation;
}

void MeshRenderer::setRotation(const glm::vec3& rotation_)
{
	rotation = rotation_;
}

glm::vec3 MeshRenderer::getRotation() const
{
	return rotation;
}

void MeshRenderer::setScale(const glm::vec3& scale_)
{
	scale = scale_;
}

glm::vec3 MeshRenderer::getScale() const
{
	return scale;
}

// Method to calculate the model matrix
glm::mat4 MeshRenderer::getModelMatrix() const
{
	glm::mat4 model = glm::mat4(1.0f);

	glm::mat4 mat_translation = glm::translate(glm::mat4(1), translation);
	glm::mat4 mat_rotation = glm::rotate(glm::mat4(1), glm::radians(rotation.x), glm::vec3(1, 0, 0));
	mat_rotation = glm::rotate(mat_rotation, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	mat_rotation = glm::rotate(mat_rotation, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	glm::mat4 mat_scale = glm::scale(glm::mat4(1), scale);
	model = mat_translation * mat_rotation * mat_scale;
	return model;
}

void MeshRenderer::setLineInfo(const glm::vec3& p1, const glm::vec3& p2, const GLfloat width)
{
	point1 = p1;
	point2 = p2;
	lineWidth = width;
}
