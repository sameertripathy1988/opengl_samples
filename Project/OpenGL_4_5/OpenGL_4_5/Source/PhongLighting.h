#pragma once
#include "BlankTest.h"
#include "MyCamera.h"
#include "MeshRenderer.h"
#include "Material.h"

class PhongLighting : public BlankTest
{
public:
	PhongLighting();
	~PhongLighting();

	void InitScene();
	void RenderScene();
	void UpdateScene();
	void UpdateButtonUp(char x);
	void UpdateMouseInput(int dx, int dy, bool bIsMouseLBDown);
	void UpdateInput(unsigned char x, int y, int z);
	void printDebugInfo();
	void RenderDefaultScene();
	
	shared_ptr<HelperShader> phongShader;
	unique_ptr<MeshRenderer> cubeMesh;

	glm::vec3 eye_pos;
	glm::vec3 light_pos;
	unique_ptr<MyCamera> mainCamera;
	glm::vec3 target_pos;

	//Lamp Mesh
	shared_ptr<HelperShader> lampShader;
	unique_ptr<MeshRenderer> lampMesh;

	//Plane
	unique_ptr<MeshRenderer> planeMesh;


	//Input
	bool enableCameraMovement;
	bool enableLightMovement;

	bool isDirty;


	GLuint tex_crate_diffuse;
	GLuint tex_crate_normal;

	GLuint tex_brick_diffuse;
	GLuint tex_brick_normal;

	glm::vec3 light_dir;
};

