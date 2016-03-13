#include "GeometryShaderSample.h"


GeometryShaderSample::GeometryShaderSample()
{
	name = "OpenGL 4.5 Geometry Shader Test";
}

GeometryShaderSample::~GeometryShaderSample()
{

}

void GeometryShaderSample::InitScene()
{
	GLfloat points[] =
	{
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};
	
	triangleShader = new HelperShader();
	triangleShader->createProgram("Triangle.vsh", "Triangle.fsh", "Triangle.gsh");

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

void GeometryShaderSample::RenderScene()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);//clear white
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(triangleShader->getProgramID());

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);

}

//Input of GS
//points - GL_POINTS(1 vertex)
//lines - GL_LINES, GL_LINE_STRIP, GL_LINE_LIST(2 vertices)
//lines_adjacency - GL_LINES_ADJACENCY, GL_LINE_STRIP_ADJACENCY(4 vertices)
//triangles - GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN(3 vertices)
//triangles_adjacency - GL_TRIANGLES_ADJACENCY, GL_TRIANGLE_STRIP_ADJACENCY(6 vertices)

//Output of GS
//points
//line_strip
//triangle_strip

