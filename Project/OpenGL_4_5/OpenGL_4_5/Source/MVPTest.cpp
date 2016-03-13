#include "MVPTest.h"
#include "ThirdParty\SOIL.h"
static float angle = 0;
static Vector camPos(0.0f, 2.0f, 5.0f);

MVPTest::MVPTest()
{
	name = "OpenGL 4.5 MVP Test";
}

MVPTest::~MVPTest()
{
}

void MVPTest::InitScene()
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
	texShader->createProgram("MVP_Texture.vsh", "MVP_Texture.fsh");


	//VBO created in memory
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	GLuint uvBuffer;
	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	
	
	GLuint textureID;
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	int width, height, channels;
	unsigned char* pixelData = NULL;
	pixelData = SOIL_load_image("Texture.png", &width, &height, &channels, 4);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)pixelData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glUseProgram(texShader->getProgramID());
	
	GLint texLoc = glGetUniformLocation(texShader->getProgramID(), "basic_texture");
	glUniform1i(texLoc, 0);
}

void MVPTest :: UpdateScene()
{
	//angle += 0.001f;
}

void MVPTest::RenderScene()
{
	glEnable(GL_BLEND);
	glViewport(0, 0, 1024, 768);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(1.0, 1.0, 1.0, 1.0);//clear white
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glUseProgram(texShader->getProgramID());

	MyMatrix mat_Model;
	MyMatrix mat_View;
	MyMatrix mat_Proj;

	//MyMatrix mat_Scale;
	//mat_Scale.scaleMatrix(0.75f, 0.75f, 0.75f);

	MyMatrix mat_Translation;
	mat_Translation.translateMatrix(2.0f, 0.0f, -6.0f);

	MyMatrix mat_RotationAbtY;
	mat_RotationAbtY.rotateMatrixAboutY(0);

	mat_Model = mat_RotationAbtY * mat_Translation;// *mat_Scale;

	mat_Proj.createPerspectiveProjectionMatrix(60.0f, 1024.0f, 768.0f, 0.1f,100.0f); //Initially camera is identity matrix i.e. camera space = world space,
																					//direction vector pointing -z i.e. inside the screen(into) 
	mat_View.lookAt(Vector(), Vector(0, 0, -1), Vector(0, 1, 0));
	//Arc ball camera
	//MyMatrix rot;
	//rot.rotateMatrixAboutY(-angle);
	//camPos =  rot * camPos;
	//mat_View.setIdentity();
	//mat_View.lookAt(camPos, Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 1.0f, 0.0f));
	//End Arc ball camera

	GLuint Ppos = glGetUniformLocation(texShader->getProgramID(), "P");
	GLuint Vpos = glGetUniformLocation(texShader->getProgramID(), "V");
	GLuint Mpos = glGetUniformLocation(texShader->getProgramID(), "M");

	glUseProgram(texShader->getProgramID());

	//glUniformMatrix4fv(Ppos, 1, GL_TRUE, &projMat->arr[0][0]);
	glUniformMatrix4fv(Ppos, 1, GL_TRUE, &mat_Proj.arr[0][0]);
	glUniformMatrix4fv(Vpos, 1, GL_TRUE, &mat_View.arr[0][0]);
	glUniformMatrix4fv(Mpos, 1, GL_TRUE, &mat_Model.arr[0][0]); //As OpenGL arranges in columns first i.e. COLUMN MAJOR MATRIX so transposed

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);

}