#include "ShadowMapping.h"
#include "Util.h"

#define PLANE_POSITION glm::vec3(0, -2, -6)
#define PLANE_SCALE glm::vec3(2.5f, 1.0f, 2.5f)

#define CUBE_POSITION glm::vec3(0, -1.75f, -6)
#define CUBE_SCALE glm::vec3(0.25f, 0.25f, 0.25f)

#define LIGHT_POSITION glm::vec3(0.3, 0.9, -9)
#define LIGHT_SCALE glm::vec3(0.05f, 0.05f, 0.05f)

#define CAMERA_POSITION glm::vec3(0, 0, 0)
#define CAMERA_TARGET PLANE_POSITION

ShadowMapping::ShadowMapping() : isDirty(false), enableCameraMovement(false), enableLightMovement(false),
light_pos(glm::vec3(0, 2, -5)), eye_pos(glm::vec3(0, 2, 0))
{
	name = "OpenGL 4.5 Shadow Mapping Test";
}

ShadowMapping::~ShadowMapping()
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

void ShadowMapping::InitScene()
{
	tex_crate_diffuse = Util::loadTexture("metal.jpg");
	tex_crate_normal = Util::loadTexture("crate_normal.png");

	tex_brick_diffuse = Util::loadTexture("Textures/brickwall.jpg");
	tex_brick_normal = Util::loadTexture("Textures/brickwall_normal.jpg");

	initShadowMapping();

	//Camera
	//-----------------------------------------------------------------------------------------
	mainCamera = make_unique<MyCamera>();
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

	//-----------------------------------------------------------------------------------------
}

void ShadowMapping::RenderScene()
{
	glEnable(GL_DEPTH_TEST);
	//glDisable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	//Render depth map in 1st Pass
	renderDepthMap();
	glCullFace(GL_BACK);
	//Fetch the depth map and Render the scene in 2nd Pass
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glClearColor(0.5, 0.5, 0.5, 1.0); // clear white
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RenderDefaultScene();
}

void ShadowMapping::UpdateScene()
{
	if (isDirty)
	{
		mainCamera->refreshViewMatrix();
		isDirty = false;
	}
}

void ShadowMapping::UpdateButtonUp(char x)
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

void ShadowMapping::UpdateMouseInput(int dx, int dy, bool bIsMouseLBDown)
{
	if (enableCameraMovement)
	{
		if(bIsMouseLBDown)
			mainCamera->processMouseMovement(dx, -dy);
	}

	if (enableLightMovement)
	{
		lampMesh->setTranslation(lampMesh->getTranslation() + glm::vec3(dx * 0.2f, -dy * 0.2f, 0));
		light_pos = lampMesh->getTranslation();
	}
	isDirty = true;
}

void ShadowMapping::UpdateInput(unsigned char x, int y, int z)
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
		mainCamera->processKeyboardMovement(direction, 0.016f);
	}
}

void ShadowMapping::printDebugInfo()
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

void ShadowMapping::initShadowMapping()
{
	//Create FBO for Depth Map
	glGenFramebuffers(1, &depthMapFBO);

	//Create Depth Map Texture
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, 2048, 2048, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	//Attach Depth Map to FBO
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//Create Depth Shader
	depthShader = make_shared<HelperShader>();
	depthShader->createProgram("DepthMap.vsh", "DepthMap.fsh");	
}

void ShadowMapping::renderDepthMap()
{
	glm::mat4 lightProjection, lightView;
	float near_plane = 0.5f, far_plane = 15.0f;
	lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
	lightView = glm::lookAt(light_pos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
	lightSpaceMatrix = lightProjection * lightView;

	//Render scene to depth map
	glViewport(0, 0, 2048, 2048);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);

	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(2.5f, 4.0f);

	depthShader->use();
	depthShader->setMat4("lightSpaceMatrix", &lightSpaceMatrix[0][0]);
	depthShader->setMat4("M", &cubeMesh->getModelMatrix()[0][0]);
	cubeMesh->render();
	depthShader->setMat4("M", &planeMesh->getModelMatrix()[0][0]);
	planeMesh->render();

	glDisable(GL_POLYGON_OFFSET_FILL);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShadowMapping::RenderDefaultScene()
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
	phongShader->setTexture("normal_map", tex_brick_normal, 1);
	phongShader->setTexture("shadow_map", depthMap, 2);

	phongShader->setMat4("P", &(mainCamera->getProjectionMatrix()[0][0]));
	phongShader->setMat4("V", &(mainCamera->getViewMatrix()[0][0]));
	phongShader->setMat4("M", &planeMesh->getModelMatrix()[0][0]);
	phongShader->setMat4("lightSpaceMatrix", &lightSpaceMatrix[0][0]);
	phongShader->setVec3("light_pos", light_pos.x, light_pos.y, light_pos.z);
	phongShader->setVec3("view_pos", mainCamera->getPosition().x, mainCamera->getPosition().y, mainCamera->getPosition().z);
	phongShader->setInt("enable_normal_map", 1);
	phongShader->setInt("enableShadow", 1);
	planeMesh->render();

	//Render Cube Mesh
	phongShader->use();
	phongShader->setTexture("diffuse_map", tex_crate_diffuse, 0);
	phongShader->setTexture("normal_map", tex_crate_normal, 1);
	phongShader->setTexture("shadow_map", depthMap, 2);

	phongShader->setMat4("P", &(mainCamera->getProjectionMatrix()[0][0]));
	phongShader->setMat4("V", &(mainCamera->getViewMatrix()[0][0]));
	phongShader->setMat4("M", &cubeMesh->getModelMatrix()[0][0]);
	phongShader->setMat4("lightSpaceMatrix", &lightSpaceMatrix[0][0]);
	phongShader->setVec3("light_pos", light_pos.x, light_pos.y, light_pos.z);
	phongShader->setVec3("view_pos", mainCamera->getPosition().x, mainCamera->getPosition().y, mainCamera->getPosition().z);
	phongShader->setInt("enable_normal_map", 0);
	phongShader->setInt("enableShadow", 1);

	cubeMesh->render();
}