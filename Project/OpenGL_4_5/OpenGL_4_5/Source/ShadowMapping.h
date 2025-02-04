#pragma once
#include "BlankTest.h"
#include "MyCamera.h"
#include "MeshRenderer.h"
#include "Material.h"

class ShadowMapping : public BlankTest
{
public:
	ShadowMapping();
	~ShadowMapping();

	void InitScene();
	void RenderScene();
	void UpdateScene();
	void UpdateButtonUp(char x);
	void UpdateMouseInput(int dx, int dy, bool bIsMouseLBDown);
	void UpdateInput(unsigned char x, int y, int z);
	void printDebugInfo();

	void initShadowMapping();
	void renderDepthMap();

	void RenderDefaultScene();

private:
	shared_ptr<HelperShader> phongShader;
	unique_ptr<MeshRenderer> cubeMesh;
	

	//Lamp Mesh
	shared_ptr<HelperShader> lampShader;
	unique_ptr<MeshRenderer> lampMesh;
	
	//Plane
	shared_ptr<HelperShader> planeShader;
	unique_ptr<MeshRenderer> planeMesh;
	

	bool isDirty;
	//Input
	bool enableCameraMovement;
	bool enableLightMovement;

	glm::vec3 eye_pos;
	glm::vec3 light_pos;
	unique_ptr<MyCamera> mainCamera;
	glm::vec3 target_pos;

	//Depth Map
	GLuint depthMapFBO;
	GLuint depthMap;
	std::shared_ptr<HelperShader> depthShader;
	
	glm::mat4 lightSpaceMatrix;

	int tex_crate_diffuse;
	int tex_crate_normal;

	int tex_brick_diffuse;
	int tex_brick_normal;
};
