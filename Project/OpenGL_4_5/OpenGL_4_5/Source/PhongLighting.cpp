#include "PhongLighting.h"
#include <Util.h>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtc/matrix_transform.hpp> 
#include "glm\glm\glm.hpp"

PhongLighting::PhongLighting()
{
	name = "OpenGL 4.5 Phong Lighting Test";
	light_pos = glm::vec3(2.2,4.4, -10.0);
	eye_pos = glm::vec3(0,7.6,0);
}

PhongLighting::~PhongLighting()
{
}

void PhongLighting::InitScene()
{
	cubeMesh = new MeshRenderer();
	cubeMesh->create(MESH_TYPE::CUBE);

	phongShader = new HelperShader();
	phongShader->createProgram("PhongLighting.vsh", "PhongLighting.fsh");
	
	phongMaterial = new Material();
	phongMaterial->setTextureInfo(TEXTURE_TYPE::DIFFUSE, "crate.png");
	phongMaterial->setShader(phongShader);

	cubeMesh->setMaterial(phongMaterial);

	

	//glUseProgram(lampShader->getProgramID());

	//glGenVertexArrays(1, &lampvao);
	//glBindVertexArray(lampvao);
	//// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	//glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//glBindVertexArray(lampvao);
	//glEnableVertexAttribArray(0);
	//// Set the vertex attributes (only position data for the lamp))
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), NULL);
	//glBindVertexArray(0);

	mainCamera = new MyCamera();
	mainCamera->setPosition(eye_pos);
	target_pos = glm::vec3(0, 0, -10);
	mainCamera->setLookAt(target_pos);

	mainCamera->refreshViewMatrix();

	glm::mat4 matrix_translation;
	matrix_translation = glm::translate(glm::mat4(1), target_pos);

	phongMaterial->apply();
	phongMaterial->linkMatrixToShader("P", &(mainCamera->getProjectionMatrix()[0][0]));
	phongMaterial->linkMatrixToShader("V", &(mainCamera->getViewMatrix()[0][0]));
	phongMaterial->linkMatrixToShader("M", &matrix_translation[0][0]);

	phongMaterial->linkVec3ToShader("light_pos", light_pos.x, light_pos.y, light_pos.z);

	//Lamp Cube Mesh
	lampMesh = new MeshRenderer();
	lampMesh->create(CUBE);

	lampShader = new HelperShader();
	lampShader->createProgram("MVP_LampFlatColor.vsh", "MVP_LampFlatColor.fsh");

	lampMaterial = new Material();
	lampMaterial->setShader(lampShader);
	lampMesh->setMaterial(lampMaterial);

	lampMaterial->apply();
	lampMaterial->linkMatrixToShader("P", &(mainCamera->getProjectionMatrix()[0][0]));
	lampMaterial->linkMatrixToShader("V", &(mainCamera->getViewMatrix()[0][0]));
	lampMaterial->linkVec3ToShader("flat_color", 1.0f, 1.0f, 1.0f);

	glm::mat4 matrix_lamp_translation;
	matrix_lamp_translation = glm::translate(glm::mat4(1), light_pos);

	glm::mat4 matrix_lamp_scale = glm::scale(glm::mat4(1), glm::vec3(0.15f, 0.15f, 0.15f));
	matrix_lamp_translation = matrix_lamp_translation * matrix_lamp_scale;

	lampMaterial->linkMatrixToShader("M", &matrix_lamp_translation[0][0]);

	//Plane
	/*planeMesh = new MeshRenderer();
	planeMesh->create(PLANE);

	planeShader = new HelperShader();
	planeShader->createProgram("PhongLighting.vsh", "PhongLighting.fsh");

	planeMaterial = new Material();
	planeMaterial->setTextureInfo(DIFFUSE, "crate.png");
	planeMaterial->setShader(phongShader);
	
	planeMesh->setMaterial(planeMaterial);
	planeMaterial->apply();
	glm::mat4 matrix_plane_translation;
	matrix_plane_translation = glm::translate(glm::mat4(1), glm::vec3(0, -1, -10));

	glm::mat4 matrix_plane_scale = glm::scale(glm::mat4(1), glm::vec3(10.0f, 10.0f, 1.0f));

	matrix_plane_translation = matrix_plane_translation * matrix_plane_scale;

	planeMaterial->linkMatrixToShader("P", &(mainCamera->getProjectionMatrix()[0][0]));
	planeMaterial->linkMatrixToShader("V", &(mainCamera->getViewMatrix()[0][0]));
	planeMaterial->linkMatrixToShader("M", &matrix_plane_translation[0][0]);
	planeMaterial->linkVec3ToShader("light_pos", light_pos.x, light_pos.y, light_pos.z);*/
}

void PhongLighting::RenderScene()
{
	glClearColor(0.2, 0.2, 0.2, 1.0);//clear white
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cubeMesh->render(CUBE);

	//planeMesh->render(CUBE);
	////Render one plane
	//glm::mat4 matrix_plane_translation;
	//matrix_plane_translation = glm::translate(glm::mat4(1), glm::vec3(0, -1, -10));

	//glm::mat4 matrix_plane_scale = glm::scale(glm::mat4(1), glm::vec3(10.0f, 0.15f, 10.0f));

	//matrix_plane_translation = matrix_plane_translation * matrix_plane_scale;

	//glUniformMatrix4fv(Modelpos, 1, GL_FALSE, &matrix_plane_translation[0][0]);

	//glBindVertexArray(vao);
	//glDrawArrays(GL_TRIANGLES, 0, 36);


	//
	//Render Light using a LAMP object
	//
	lampMesh->render(CUBE);
}

void PhongLighting::UpdateScene()
{
	mainCamera->refreshViewMatrix();
}

void PhongLighting::UpdateInput(char x, int y, int z)
{
	switch (x)
	{
	case GLUT_KEY_DOWN://Q //Decrease the ambient Light
		
		break;
	case GLUT_KEY_UP://W //Increase the ambient Light
		
		break;
	default:
		break;
	}
}

void PhongLighting::UpdateButtonUp(char x)
{
	switch (x)
	{
	case 'c':
		enableCameraMovement = !enableCameraMovement;
		break;
	case 'l':
		enableLightMovement = !enableLightMovement;
		break;
	case 'f':
		enableLightMovement = false;
		enableCameraMovement = false;
		break;
	case 'd':
		printDebugInfo();
		break;
	default:
		break;
	}
}

void PhongLighting::UpdateMouseInput(int dx, int dy, bool bIsMouseLBDown)
{
	if (enableCameraMovement)
		mainCamera->setOffsetPosition(glm::vec3(0, dy * 0.2f, 0));
	if(enableLightMovement)
		light_pos += glm::vec3(dx*0.2f, -dy * 0.2f, 0);
}

void PhongLighting::printDebugInfo()
{
	cout << "Main Camera " << endl
		<< mainCamera->getPosition().x << endl
		<< mainCamera->getPosition().y << endl
		<< mainCamera->getPosition().z << endl;

	cout << "Light Position " << endl
		<< light_pos.x << endl
		<< light_pos.y << endl
		<< light_pos.z << endl;
}

