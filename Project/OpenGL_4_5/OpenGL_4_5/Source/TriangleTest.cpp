#include "TriangleTest.h"


TriangleTest::TriangleTest()
{
	name = "OpenGL 4.5 Triangle";
}

TriangleTest::~TriangleTest()
{

}

void TriangleTest::InitScene()
{
	GLfloat points[] =
	{
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};
	
	triangleShader = new HelperShader();
	triangleShader->createProgram("Triangle.vsh", "Triangle.fsh");

	//VBO created in memory
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	//VAO created
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//VAO attached to VBO
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void TriangleTest::RenderScene()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);//clear white
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(triangleShader->getProgramID());

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);

}