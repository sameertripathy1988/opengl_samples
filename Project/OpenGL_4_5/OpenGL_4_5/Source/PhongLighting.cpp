#include "PhongLighting.h"
#include "Util.h"

#define PLANE_POSITION glm::vec3(0, -2, -6)
#define PLANE_SCALE glm::vec3(2.5f, 1.0f, 2.5f)

#define CUBE_POSITION glm::vec3(0, -1.75f, -6)
#define CUBE_SCALE glm::vec3(0.25f, 0.25f, 0.25f)

#define LIGHT_POSITION glm::vec3(0.3, 0.9, -9)
#define LIGHT_SCALE glm::vec3(0.05f, 0.05f, 0.05f)
#define LIGHT_DIRECTION CUBE_POSITION-LIGHT_POSITION

#define CAMERA_POSITION glm::vec3(0, 0, 0)
#define CAMERA_TARGET PLANE_POSITION


PhongLighting::PhongLighting() : isDirty(false), enableCameraMovement(false), enableLightMovement(false),
light_pos(glm::vec3(0, 2, -5)), eye_pos(glm::vec3(0, 2, 0))
{
	name = "OpenGL 4.5 Directional Lighting Test";
}

PhongLighting::~PhongLighting()
{
	if (tex_crate_diffuse)
	{
		glDeleteTextures(1, &tex_crate_diffuse);
	}
	if (tex_crate_normal)
	{
		glDeleteTextures(1, &tex_crate_normal);
	}
	if (tex_brick_diffuse)
	{
		glDeleteTextures(1, &tex_brick_diffuse);
	}
	if (tex_brick_normal)
	{
		glDeleteTextures(1, &tex_brick_normal);
	}
}

void PhongLighting::InitScene()
{
	tex_crate_diffuse = Util::loadTexture("crate.png");
	tex_crate_normal = Util::loadTexture("crate_normal.png");

	tex_brick_diffuse = Util::loadTexture("Textures/brickwall.jpg");
	tex_brick_normal = Util::loadTexture("Textures/brickwall_normal.jpg");

	//Camera
	//-----------------------------------------------------------------------------------------
	mainCamera = make_unique<MyCamera>();
	mainCamera->setPosition(CAMERA_POSITION);
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
	phongShader->createProgram("DirectionalLight.vert", "DirectionalLight.frag");

	//-----------------------------------------------------------------------------------------

	//Plane Mesh
	//-----------------------------------------------------------------------------------------
	planeMesh = make_unique<MeshRenderer>();
	planeMesh->create(PLANE);
	planeMesh->setTranslation(PLANE_POSITION);
	planeMesh->setScale(PLANE_SCALE);

	//-----------------------------------------------------------------------------------------

	//Lamp Cube Mesh
	//-----------------------------------------------------------------------------------------
	lampMesh = make_unique<MeshRenderer>();
	lampMesh->create(CUBE);
	lampMesh->setTranslation(LIGHT_POSITION);
	lampMesh->setScale(LIGHT_SCALE);

	lampShader = make_shared<HelperShader>();
	lampShader->createProgram("MVP_LampFlatColor.vsh", "MVP_LampFlatColor.fsh");

	light_pos = LIGHT_DIRECTION;



	//-----------------------------------------------------------------------------------------
}

void PhongLighting::RenderScene()
{
	glEnable(GL_DEPTH_TEST);
	//Fetch the depth map and Render the scene in 2nd Pass
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glClearColor(0.5, 0.5, 0.5, 1.0); // clear white
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RenderDefaultScene();
}

void PhongLighting::UpdateScene()
{
	if (isDirty)
	{
		mainCamera->refreshViewMatrix();
		isDirty = false;
	}
}

void PhongLighting::UpdateButtonUp(char x)
{
	switch (x)
	{
	case 'm':
		enableCameraMovement = !enableCameraMovement;
		break;
	case 'l':
		enableLightMovement = !enableLightMovement;
		break;
	case 'f':
		enableLightMovement = false;
		enableCameraMovement = false;
		break;
	case 'u':
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
		if (bIsMouseLBDown)
			mainCamera->processMouseMovement(dx, -dy);
	}

	if (enableLightMovement)
	{
		lampMesh->setTranslation(lampMesh->getTranslation() + glm::vec3(dx * 0.2f, -dy * 0.2f, 0));
		light_pos = lampMesh->getTranslation();
		light_dir = CUBE_POSITION - light_pos;
	}
	isDirty = true;
}

void PhongLighting::UpdateInput(unsigned char x, int y, int z)
{

	if (enableCameraMovement)
	{
		glm::vec3 direction(0.0f);
		switch (x) {
		case 'w':
			direction.z = 1.0f;
			break;
		case 's':
			direction.z = -1.0f;
			break;
		case 'a':
			direction.x = -1.0f;
			break;
		case 'd':
			direction.x = 1.0f;
			break;
		case 'q':
			direction.y = 1.0f;
			break;
		case 'e':
			direction.y = -1.0f;
			break;
		default:
			break;
		}
		cout << Util::delta_time << endl;
		mainCamera->processKeyboardMovement(direction, 0.016f);
	}
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

void PhongLighting::RenderDefaultScene()
{

	lampShader->use();
	lampShader->setMat4("P", &(mainCamera->getProjectionMatrix()[0][0]));
	lampShader->setMat4("V", &(mainCamera->getViewMatrix()[0][0]));
	lampShader->setMat4("M", &lampMesh->getModelMatrix()[0][0]);
	lampShader->setVec3("flat_color", 1.0f, 1.0f, 1.0f);
	lampMesh->render();

	//Render Plane Mesh
	phongShader->use();

	phongShader->setTexture("diffuse_map", tex_brick_diffuse, 0);

	phongShader->setMat4("P", &(mainCamera->getProjectionMatrix()[0][0]));
	phongShader->setMat4("V", &(mainCamera->getViewMatrix()[0][0]));
	phongShader->setMat4("M", &planeMesh->getModelMatrix()[0][0]);
	phongShader->setVec3("light_dir", light_dir.x, light_dir.y, light_dir.z);
	phongShader->setVec3("view_pos", mainCamera->getPosition().x, mainCamera->getPosition().y, mainCamera->getPosition().z);

	planeMesh->render();

	//Render Cube Mesh
	phongShader->use();
	phongShader->setTexture("diffuse_map", tex_crate_diffuse, 0);
	

	phongShader->setMat4("P", &(mainCamera->getProjectionMatrix()[0][0]));
	phongShader->setMat4("V", &(mainCamera->getViewMatrix()[0][0]));
	phongShader->setMat4("M", &cubeMesh->getModelMatrix()[0][0]);
	phongShader->setVec3("light_dir", light_dir.x, light_dir.y, light_dir.z);
	phongShader->setVec3("view_pos", mainCamera->getPosition().x, mainCamera->getPosition().y, mainCamera->getPosition().z);

	cubeMesh->render();
}