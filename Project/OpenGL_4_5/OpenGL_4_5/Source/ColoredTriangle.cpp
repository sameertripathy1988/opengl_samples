#include "ColoredTriangle.h"


ColoredTriangle::ColoredTriangle()
{
	name = "OpenGL 4.5 Colored Triangle";
}

ColoredTriangle::~ColoredTriangle()
{
}

void ColoredTriangle::InitScene()
{
	GLfloat points[] =
	{
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};

	GLfloat colors[] =
	{
		1.0f, 0.0f, 0.0f,1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f
	};
	
	colTriangleShader = new HelperShader();
	colTriangleShader->createProgram("ColoredTriangle.vsh", "ColoredTriangle.fsh");

	//VBO created in memory
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	GLuint colVbo;
	glGenBuffers(1, &colVbo);
	glBindBuffer(GL_ARRAY_BUFFER, colVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	//VAO created
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//VAO attached to VBO
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colVbo);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
}

void ColoredTriangle::RenderScene()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);//CLEAR WHITE
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(colTriangleShader->getProgramID());

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);

}