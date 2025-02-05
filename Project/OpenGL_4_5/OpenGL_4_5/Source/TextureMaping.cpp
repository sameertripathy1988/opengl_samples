#include "TextureMaping.h"

#include "ThirdParty\SOIL.h"

#include "Util.h"
#include "TextureManager.h"

TextureMaping::TextureMaping()
{
	name = "OpenGL 4.5 Texture Maping";
}
TextureMaping::~TextureMaping()
{
	TextureManager::getInstance().clearTextures();
}

void TextureMaping::InitScene()
{
	GLfloat points[] =
	{
		-0.5f, 0.5f, 0.0f, //0,1
		0.5f, 0.5f, 0.0f,  //1,1
		0.5f, -0.5f, 0.0f, //1,0
		-0.5f, -0.5f, 0.0f //0,0
	};


	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;


	/*GLfloat uv[] = { 0, 1.0,
		1.0, 1.0,
		1.0, 0,
		0, 1.0,
		1.0, 0,
		0, 0
		};*/

	//Inverted Y
	GLfloat uv[] = { 0, 0.0,
	1.0, 0.0,
	1.0, 1,
	0, 1
	};


	texShader = new HelperShader();
	texShader->createProgram("Texture.vsh", "Texture.fsh");
	

	//VBO created in memory
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	GLuint uvBuffer;
	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER,sizeof(uv), uv, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL); 
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	texture = TextureManager::getInstance().loadTexture("Texture.png");

	glUseProgram(texShader->getProgramID());

	texShader->setTexture("diffuse_map", texture, 0);

}
void TextureMaping::RenderScene()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(1.0, 1.0, 1.0, 1.0);//clear white
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glUseProgram(texShader->getProgramID());

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);
}