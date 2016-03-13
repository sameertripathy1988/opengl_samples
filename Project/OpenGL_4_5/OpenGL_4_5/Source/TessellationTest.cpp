#include "TessellationTest.h"


TessellationTest::TessellationTest()
{
	name = "OpenGL 4.5 Tessellation Test";
}

TessellationTest::~TessellationTest()
{

}

void TessellationTest::InitScene()
{
	GLfloat points[] =
	{
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};
	
	triangleShader = new HelperShader();
	triangleShader->createProgram("TessTriangle.vsh", "TessTriangle.fsh",NULL, "TessTriangle.tcsh", "TessTriangle.tesh");

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

	GLint maxPatchvertices = 0;
	glGetIntegerv(GL_MAX_PATCH_VERTICES, &maxPatchvertices);
	printf("Max supported Patch vertices %d",maxPatchvertices);
	//Set Input patch vertices count
	glPatchParameteri(GL_PATCH_VERTICES, 3);
}

void TessellationTest::RenderScene()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);//clear white
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(triangleShader->getProgramID());

	glBindVertexArray(vao);
	glDrawArrays(GL_PATCHES, 0, 3);

}