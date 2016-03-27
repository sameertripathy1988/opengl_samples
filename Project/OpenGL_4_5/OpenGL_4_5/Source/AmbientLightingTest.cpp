#include "AmbientLightingTest.h"
#include "ThirdParty\SOIL.h"

#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtc/matrix_transform.hpp> 


float AmbientLightingTest::ambientStrength;

AmbientLightingTest::AmbientLightingTest()
{
	name = "OpenGL 4.5 Ambient Lighting Test";
	lightColor = glm::vec3(1.0, 1.0, 1.0);
	AmbientLightingTest::ambientStrength = 0.5f;
	eye_pos = glm::vec3(0, 2, -2);
}

AmbientLightingTest::~AmbientLightingTest()
{
	delete mainCamera;
}

void AmbientLightingTest::InitScene()
{
	GLfloat vertexData[] = {
		//  X     Y     Z       U     V          Normal
		// bottom
		-1.0f,-1.0f,-1.0f,   0.0f, 0.0f,   0.0f, -1.0f, 0.0f,
		1.0f,-1.0f,-1.0f,   1.0f, 0.0f,   0.0f, -1.0f, 0.0f,
		-1.0f,-1.0f, 1.0f,   0.0f, 1.0f,   0.0f, -1.0f, 0.0f,
		1.0f,-1.0f,-1.0f,   1.0f, 0.0f,   0.0f, -1.0f, 0.0f,
		1.0f,-1.0f, 1.0f,   1.0f, 1.0f,   0.0f, -1.0f, 0.0f,
		-1.0f,-1.0f, 1.0f,   0.0f, 1.0f,   0.0f, -1.0f, 0.0f,

		// top
		-1.0f, 1.0f,-1.0f,   0.0f, 0.0f,   0.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 1.0f,   0.0f, 1.0f,   0.0f, 1.0f, 0.0f,
		1.0f, 1.0f,-1.0f,   1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
		1.0f, 1.0f,-1.0f,   1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 1.0f,   0.0f, 1.0f,   0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   0.0f, 1.0f, 0.0f,

		// front
		-1.0f,-1.0f, 1.0f,   1.0f, 0.0f,   0.0f, 0.0f, 1.0f,
		1.0f,-1.0f, 1.0f,   0.0f, 0.0f,   0.0f, 0.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   0.0f, 0.0f, 1.0f,
		1.0f,-1.0f, 1.0f,   0.0f, 0.0f,   0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,   0.0f, 1.0f,   0.0f, 0.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   0.0f, 0.0f, 1.0f,

		// back
		-1.0f,-1.0f,-1.0f,   0.0f, 0.0f,   0.0f, 0.0f, -1.0f,
		-1.0f, 1.0f,-1.0f,   0.0f, 1.0f,   0.0f, 0.0f, -1.0f,
		1.0f,-1.0f,-1.0f,   1.0f, 0.0f,   0.0f, 0.0f, -1.0f,
		1.0f,-1.0f,-1.0f,   1.0f, 0.0f,   0.0f, 0.0f, -1.0f,
		-1.0f, 1.0f,-1.0f,   0.0f, 1.0f,   0.0f, 0.0f, -1.0f,
		1.0f, 1.0f,-1.0f,   1.0f, 1.0f,   0.0f, 0.0f, -1.0f,

		// left
		-1.0f,-1.0f, 1.0f,   0.0f, 1.0f,   -1.0f, 0.0f, 0.0f,
		-1.0f, 1.0f,-1.0f,   1.0f, 0.0f,   -1.0f, 0.0f, 0.0f,
		-1.0f,-1.0f,-1.0f,   0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,
		-1.0f,-1.0f, 1.0f,   0.0f, 1.0f,   -1.0f, 0.0f, 0.0f,
		-1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   -1.0f, 0.0f, 0.0f,
		-1.0f, 1.0f,-1.0f,   1.0f, 0.0f,   -1.0f, 0.0f, 0.0f,

		// right
		1.0f,-1.0f, 1.0f,   1.0f, 1.0f,   1.0f, 0.0f, 0.0f,
		1.0f,-1.0f,-1.0f,   1.0f, 0.0f,   1.0f, 0.0f, 0.0f,
		1.0f, 1.0f,-1.0f,   0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
		1.0f,-1.0f, 1.0f,   1.0f, 1.0f,   1.0f, 0.0f, 0.0f,
		1.0f, 1.0f,-1.0f,   0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,   0.0f, 1.0f,   1.0f, 0.0f, 0.0f
	};

	triangleShader = new HelperShader();
	triangleShader->createProgram("Lighting.vsh", "Lighting.fsh");

	//VBO created in memory
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	//VAO created
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//VAO attached to VBO
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), NULL);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, 8 * sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));
	
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, 8 * sizeof(GLfloat), (const GLvoid*)(5 * sizeof(GLfloat)));

	GLuint textureID;
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	int width, height, channels;
	unsigned char* pixelData = NULL;
	pixelData = SOIL_load_image("crate.png", &width, &height, &channels, 4);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)pixelData);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glUseProgram(triangleShader->getProgramID());

	GLint texLoc = glGetUniformLocation(triangleShader->getProgramID(), "basic_texture");
	glUniform1i(texLoc, 0);

	mainCamera = new MyCamera();
	mainCamera->setPosition(eye_pos);
	glm::vec3 target_pos = glm::vec3(0, 0, -10);
	mainCamera->setLookAt(target_pos);
	mainCamera->SetIsNoLockedTarget(false);
}

glm::vec3 lightColor = glm::vec3(1.0, 1, 1.0);
static float ambientStrength = 1.0f;
static float fov = 60.0f;
void AmbientLightingTest::RenderScene()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);//clear white
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(triangleShader->getProgramID());
	
	
	glm::mat4 matrix_translation;
	matrix_translation = glm::translate(glm::mat4(1), glm::vec3(0, 0, -10));

	//View Matrix
	glm::mat4 matrix_view;
	matrix_view = mainCamera->getViewMatrix();

	//Projection Matrix
	glm::mat4 matrix_projection = mainCamera->getProjectionMatrix();

	GLuint Projpos = glGetUniformLocation(triangleShader->getProgramID(), "P");
	GLuint Viewpos = glGetUniformLocation(triangleShader->getProgramID(), "V");
	GLuint Modelpos = glGetUniformLocation(triangleShader->getProgramID(), "M");

	glUseProgram(triangleShader->getProgramID());

	glUniformMatrix4fv(Projpos, 1, GL_FALSE, &matrix_projection[0][0]);
	glUniformMatrix4fv(Viewpos, 1, GL_FALSE, &matrix_view[0][0]);
	glUniformMatrix4fv(Modelpos, 1, GL_FALSE, &matrix_translation[0][0]);

	glUniform3f(glGetUniformLocation(triangleShader->getProgramID(), "light_color"), lightColor.r, lightColor.g, lightColor.b);
	glUniform1f(glGetUniformLocation(triangleShader->getProgramID(), "ambient_strength"), ambientStrength);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void AmbientLightingTest::UpdateScene()
{
	mainCamera->refreshViewMatrix();
}

void AmbientLightingTest::UpdateMouseWheel(int wheel, int direction, int x, int y)
{
	mainCamera->setFOV(mainCamera->getFOV() - direction);

	printf("%d , %d", x, y);
	//mainCamera->setLookAt(glm::vec3(0, 0, -1.0f));
}

void AmbientLightingTest::UpdateInput(int x, int y, int z)
{
	UpdateCameraOnInput(x);
	switch (x)
	{
	case 113://Q //Decrease the ambient Light
			 if (ambientStrength > 0)
			 	ambientStrength -= 0.1f;
		break;
	case 119://W //Increase the ambient Light
			 if(ambientStrength < 1)
			 	ambientStrength += 0.1f;
			 break;
	default:
		break;
	}
}

void AmbientLightingTest::UpdateCameraOnInput(int x)
{
	switch (x)
	{
	case 100://LEFT
		mainCamera->setOffsetPosition(glm::vec3(-0.2, 0, 0));
		break;
	case 101://UP
		mainCamera->setOffsetPosition(glm::vec3(0, 0.2f, 0));
		break;
	case 102://RIGHT
		mainCamera->setOffsetPosition(glm::vec3(0.2, 0, 0));
		break;
	case 103://DOWN
		mainCamera->setOffsetPosition(glm::vec3(0, -0.2f, 0));
		break;
	case 122://Z
		mainCamera->setOffsetPosition(glm::vec3(0, 0, -0.2f));
		break;
	case 120://X
		mainCamera->setOffsetPosition(glm::vec3(0, 0, 0.2f));
		break;
	}
}
