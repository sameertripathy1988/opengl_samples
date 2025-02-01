#include "PhongLighting.h"
#include <Util.h>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtc/matrix_transform.hpp> 
#include "glm\glm\glm.hpp"

#define PLANE_POSITION glm::vec3(0, -2, -3)
#define PLANE_SCALE glm::vec3(1.5f, 1.0f, 1.5f)

#define CUBE_POSITION glm::vec3(0, -1.74f, -3)
#define CUBE_SCALE glm::vec3(0.25f, 0.25f, 0.25f)

#define LIGHT_POSITION glm::vec3(0, -1.2, -3)
#define LIGHT_SCALE glm::vec3(0.05f, 0.05f, 0.05f)

#define CAMERA_POSITION glm::vec3(0, 0, 0)
#define CAMERA_TARGET PLANE_POSITION

float rot = 0.0f;
PhongLighting::PhongLighting() : isDirty(false), enableCameraMovement(false), enableLightMovement(false), 
light_pos(glm::vec3(0, 2, -5)), eye_pos(glm::vec3(0, 2, 0))
{
	name = "OpenGL 4.5 Phong Lighting Test";
}

PhongLighting::~PhongLighting()
{
}

void PhongLighting::InitScene()
{
	//Camera
	//-----------------------------------------------------------------------------------------
	mainCamera = new MyCamera();
	mainCamera->setPosition(CAMERA_POSITION);
	target_pos = glm::vec3(0, 0, -5);
	mainCamera->setLookAt(CAMERA_TARGET); //Cube Position

	mainCamera->refreshViewMatrix();
	//-----------------------------------------------------------------------------------------
	
	//Cube Mesh
	//-----------------------------------------------------------------------------------------
	cubeMesh = make_unique<MeshRenderer>();
	cubeMesh->create(MESH_TYPE::CUBE);
	cubeMesh->setTranslation(CUBE_POSITION);
	cubeMesh->setScale(CUBE_SCALE);

	phongShader = make_shared<HelperShader>();
	phongShader->createProgram("PhongLighting.vsh", "PhongLighting.fsh");

	phongMaterial = make_shared<Material>();
	phongMaterial->setTextureInfo(TEXTURE_TYPE::DIFFUSE, "crate.png");
	phongMaterial->setShader(phongShader);

	cubeMesh->setMaterial(phongMaterial);

	phongMaterial->bind();
	phongMaterial->linkMatrixToShader("P", &(mainCamera->getProjectionMatrix()[0][0]));
	phongMaterial->linkMatrixToShader("V", &(mainCamera->getViewMatrix()[0][0]));
	phongMaterial->linkMatrixToShader("M", &cubeMesh->getModelMatrix()[0][0]);
	phongMaterial->linkVec3ToShader("light_pos", LIGHT_POSITION.x, LIGHT_POSITION.y, LIGHT_POSITION.z);
	phongMaterial->unbind();
	//-----------------------------------------------------------------------------------------
	
	//Plane Mesh
	//-----------------------------------------------------------------------------------------
	planeMesh = make_unique<MeshRenderer>();
	planeMesh->create(PLANE);
	planeMesh->setTranslation(PLANE_POSITION);
	planeMesh->setScale(PLANE_SCALE);

	planeShader = make_shared<HelperShader>();
	planeShader->createProgram("PhongLighting.vsh", "PhongLighting.fsh");

	planeMaterial = make_shared<Material>();
	planeMaterial->setTextureInfo(TEXTURE_TYPE::DIFFUSE, "Textures/brickwall.jpg");
	planeMaterial->setShader(planeShader);
	planeMaterial->bind();

	planeMesh->setMaterial(planeMaterial);

	planeMaterial->linkMatrixToShader("P", &(mainCamera->getProjectionMatrix()[0][0]));
	planeMaterial->linkMatrixToShader("V", &(mainCamera->getViewMatrix()[0][0]));
	planeMaterial->linkMatrixToShader("M", &planeMesh->getModelMatrix()[0][0]);
	planeMaterial->linkVec3ToShader("light_pos", LIGHT_POSITION.x, LIGHT_POSITION.y, LIGHT_POSITION.z);
	planeMaterial->unbind();

	//-----------------------------------------------------------------------------------------

	//Lamp Cube Mesh
	//-----------------------------------------------------------------------------------------
	lampMesh = make_unique<MeshRenderer>();
	lampMesh->create(CUBE);
	lampMesh->setTranslation(LIGHT_POSITION);
	lampMesh->setScale(LIGHT_SCALE);

	lampShader = make_shared<HelperShader>();
	lampShader->createProgram("MVP_LampFlatColor.vsh", "MVP_LampFlatColor.fsh");

	lampMaterial = make_shared<Material>();
	lampMaterial->setShader(lampShader);
	lampMaterial->bind();

	lampMesh->setMaterial(lampMaterial);
	
	lampMaterial->linkMatrixToShader("P", &(mainCamera->getProjectionMatrix()[0][0]));
	lampMaterial->linkMatrixToShader("V", &(mainCamera->getViewMatrix()[0][0]));
	lampMaterial->linkMatrixToShader("M", &lampMesh->getModelMatrix()[0][0]);
	lampMaterial->linkVec3ToShader("flat_color", 1.0f, 1.0f, 1.0f);
	
	//-----------------------------------------------------------------------------------------
}

void PhongLighting::RenderScene()
{
	glClearColor(0.25, 0.25, 0.25, 1.0); // clear white
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render Lamp Mesh
	
	lampMesh->render();
	
	//// Render Plane Mesh
	
	planeMesh->render();
	
	// Render Cube Mesh
	
	cubeMesh->render();
	
	
}

void PhongLighting::UpdateScene()
{
	if (isDirty)
	{
		mainCamera->refreshViewMatrix();
		lampMaterial->linkMatrixToShader("P", &(mainCamera->getProjectionMatrix()[0][0]));
		lampMaterial->linkMatrixToShader("V", &(mainCamera->getViewMatrix()[0][0]));

		phongMaterial->linkMatrixToShader("P", &(mainCamera->getProjectionMatrix()[0][0]));
		phongMaterial->linkMatrixToShader("V", &(mainCamera->getViewMatrix()[0][0]));

		planeMaterial->linkMatrixToShader("P", &(mainCamera->getProjectionMatrix()[0][0]));
		planeMaterial->linkMatrixToShader("V", &(mainCamera->getViewMatrix()[0][0]));

		phongMaterial->linkVec3ToShader("light_pos", light_pos.x, light_pos.y, light_pos.z);
		
		isDirty = false;
	}
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
	{
		mainCamera->setOffsetPosition(glm::vec3(0, dy * 0.2f, 0));
		mainCamera->refreshViewMatrix();
		/*rot += dx * 0.2f;
		planeMesh->setRotation(glm::vec3(rot, 0, 0));*/
		//planeMaterial->linkMatrixToShader("M", &planeMesh->getModelMatrix()[0][0]);
	}

	if(enableLightMovement)
	{
		lampMesh->setTranslation(lampMesh->getTranslation() + glm::vec3(dx * 0.2f, -dy * 0.2f, 0));
		light_pos = lampMesh->getTranslation();
	}
	isDirty = true;
}

void PhongLighting::printDebugInfo()
{
	cout << "Main Camera " << endl
		<< mainCamera->getPosition().x << endl
		<< mainCamera->getPosition().y << endl
		<< mainCamera->getPosition().z << endl;

	cout << "Light Position " << endl
		<< lampMesh->getTranslation().x << endl
		<< lampMesh->getTranslation().y << endl
		<< lampMesh->getTranslation().z << endl;
}

