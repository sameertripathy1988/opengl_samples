#include "MeshRenderer.h"
#include "GeometryData.h"

MeshRenderer::MeshRenderer()
{
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::render(MESH_TYPE meshType)
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
	default:
		break;
	}
}

void MeshRenderer::create(MESH_TYPE meshType)
{
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
		default:
			break;
	}
}

void MeshRenderer::setMaterial(Material*& material_)
{
	material = material_;
}

void MeshRenderer::createPlane()
{
	//VBO created in memory
	glGenBuffers(1, &plane_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, plane_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(plane_pos_uv_n), plane_pos_uv_n, GL_STATIC_DRAW);

	//VAO created
	glGenVertexArrays(1, &plane_vao);
	glBindVertexArray(plane_vao);

	//VAO attached to VBO
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, plane_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), NULL);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, 8 * sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, 8 * sizeof(GLfloat), (const GLvoid*)(5 * sizeof(GLfloat)));
}

void MeshRenderer::createCube()
{
	//VBO created in memory
	glGenBuffers(1, &cube_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, cube_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_pos_uv_n), cube_pos_uv_n, GL_STATIC_DRAW);

	//VAO created
	glGenVertexArrays(1, &cube_vao);
	glBindVertexArray(cube_vao);

	//VAO attached to VBO
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, cube_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), NULL);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, 8 * sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, 8 * sizeof(GLfloat), (const GLvoid*)(5 * sizeof(GLfloat)));
}

void MeshRenderer::createModel()
{
}

void MeshRenderer::renderPlane()
{
	glUseProgram(material->shader->getProgramID());
	glBindVertexArray(plane_vbo);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void MeshRenderer::renderCube()
{
	glUseProgram(material->shader->getProgramID());
	glBindVertexArray(cube_vbo);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void MeshRenderer::renderModel()
{
}
