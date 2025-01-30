#include "DiffuseLightingTest.h"
#include "ThirdParty\SOIL.h"
#include "glm\glm\glm.hpp"
#include "Camera.h"
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtc/matrix_transform.hpp> 
#include <Util.h>

using namespace tdogl;

float DiffuseLightingTest::ambientStrength;

//Press C to toggle lightmovement and camera movement
//Up/Down arrow to move camera up/down when camera movement toggled ON
//Left/Right/up/down to move the light source when light movement toggled ON


DiffuseLightingTest::DiffuseLightingTest()
{
	name = "OpenGL 4.5 Diffuse Lighting Test";
	lightColor = glm::vec3(1.0, 1.0, 1.0);
	light_pos = glm::vec3(1.0, 2, -10.0);
	ambientStrength = 0.5f;
	eye_pos = glm::vec3(0, 2, -2);
	target_pos = glm::vec3(0, 0, -10);
	isLightMovementOn = false;
}

DiffuseLightingTest::~DiffuseLightingTest()
{

}

void DiffuseLightingTest::InitScene()
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

	diffuseShader = new HelperShader();
	diffuseShader->createProgram("DiffuseLighting.vsh", "DiffuseLighting.fsh");

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

	GLuint tex_id = Util::loadTexture("crate.png");

	glUseProgram(diffuseShader->getProgramID());

	GLint texLoc = glGetUniformLocation(diffuseShader->getProgramID(), "basic_texture");
	glUniform1i(texLoc, 0);


	lampShader = new HelperShader();
	lampShader->createProgram("MVP_LampFlatColor.vsh", "MVP_LampFlatColor.fsh");
	glUseProgram(lampShader->getProgramID());

	glGenVertexArrays(1, &lampvao);
	glBindVertexArray(lampvao);
	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBindVertexArray(lampvao);
	glEnableVertexAttribArray(0);
	// Set the vertex attributes (only position data for the lamp))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), NULL);
	glBindVertexArray(0);

	mainCamera = new MyCamera();
	mainCamera->setPosition(eye_pos);
	glm::vec3 target_pos = glm::vec3(0, 0, -10);
	mainCamera->setLookAt(target_pos);
}

void DiffuseLightingTest::RenderScene()
{
	glClearColor(0.2, 0.2, 0.2, 1.0);//clear white
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(diffuseShader->getProgramID());
	
	glm::mat4 matrix_view;
	matrix_view = mainCamera->getViewMatrix();
	
	glm::mat4 matrix_translation;
	matrix_translation = glm::translate(glm::mat4(1), target_pos);

	glm::mat4 matrix_projection = mainCamera->getProjectionMatrix();

	GLuint Projpos = glGetUniformLocation(diffuseShader->getProgramID(), "P");
	GLuint Viewpos = glGetUniformLocation(diffuseShader->getProgramID(), "V");
	GLuint Modelpos = glGetUniformLocation(diffuseShader->getProgramID(), "M");

	glUseProgram(diffuseShader->getProgramID());

	glUniformMatrix4fv(Projpos, 1, GL_FALSE, &matrix_projection[0][0]);
	glUniformMatrix4fv(Viewpos, 1, GL_FALSE, &matrix_view[0][0]);
	glUniformMatrix4fv(Modelpos, 1, GL_FALSE, &matrix_translation[0][0]);

	//glUniformMatrix4fv(glGetUniformLocation(triangleShader->getProgramID(), "normal_matrix"), 1, GL_TRUE, &matrix_normal[0][0]);

	glUniform3f(glGetUniformLocation(diffuseShader->getProgramID(), "light_color"), lightColor.r, lightColor.g, lightColor.b);
	glUniform1f(glGetUniformLocation(diffuseShader->getProgramID(), "ambient_strength"), ambientStrength);
	glUniform3f(glGetUniformLocation(diffuseShader->getProgramID(), "light_pos"), light_pos.x,light_pos.y,light_pos.z);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	
	//Render one plane
	glm::mat4 matrix_plane_translation;
	matrix_plane_translation = glm::translate(glm::mat4(1), glm::vec3(0,-1,-10));

	glm::mat4 matrix_plane_scale = glm::scale(glm::mat4(1), glm::vec3(10.0f, 0.15f, 10.0f));

	matrix_plane_translation = matrix_plane_translation * matrix_plane_scale;
	
	glUniformMatrix4fv(Modelpos, 1, GL_FALSE, &matrix_plane_translation[0][0]);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	
	
	//
	//Render Light using a LAMP object
	//

	glUseProgram(lampShader->getProgramID());

	glm::mat4 matrix_lamp_translation;
	matrix_lamp_translation = glm::translate(glm::mat4(1), light_pos);

	glm::mat4 matrix_lamp_scale  = glm::scale(glm::mat4(1), glm::vec3(0.15f, 0.15f, 0.15f));

	matrix_lamp_translation = matrix_lamp_translation * matrix_lamp_scale;

	glUseProgram(lampShader->getProgramID());

	glUniformMatrix4fv(glGetUniformLocation(lampShader->getProgramID(), "P"), 1, GL_FALSE, &matrix_projection[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(lampShader->getProgramID(), "V"), 1, GL_FALSE, &matrix_view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(lampShader->getProgramID(), "M"), 1, GL_FALSE, &matrix_lamp_translation[0][0]);

	glUniform3f(glGetUniformLocation(lampShader->getProgramID(), "flat_color"), 1.0f, 1.0f, 1.0f);

	glBindVertexArray(lampvao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void DiffuseLightingTest::UpdateScene()
{
	mainCamera->refreshViewMatrix();
}

void DiffuseLightingTest::UpdateMouseWheel(int wheel, int direction, int x, int y)
{
	mainCamera->setFOV(mainCamera->getFOV() - direction);
}

void DiffuseLightingTest:: UpdateInput(int x, int y, int z)
{
	UpdateCameraOnInput(x);
	switch (x)
	{
	case 99:
		isLightMovementOn = !isLightMovementOn;
		break;
	case 106://J
			light_pos.x -= 0.1f;
		break;
	case 107://K
			light_pos.z += 0.1f;
		break;
	case 108://L
			light_pos.x += 0.1f;
		break;
	case 105://I
			light_pos.z -= 0.1f;
		break;
	case 113://Q //Decrease the ambient Light
		if (ambientStrength > 0)
			ambientStrength -= 0.1f;
		break;
	case 119://W //Increase the ambient Light
		if (ambientStrength < 1)
			ambientStrength += 0.1f;
		break;
	default:
		break;
	}
}


void DiffuseLightingTest::UpdateCameraOnInput(int x)
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