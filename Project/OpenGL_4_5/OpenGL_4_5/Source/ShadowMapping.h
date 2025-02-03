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
	void printDebugInfo();

private:
	shared_ptr<HelperShader> phongShader;
	unique_ptr<MeshRenderer> cubeMesh;
	shared_ptr<Material> phongMaterial;

	//Lamp Mesh
	shared_ptr<HelperShader> lampShader;
	unique_ptr<MeshRenderer> lampMesh;
	shared_ptr<Material>lampMaterial;
	//Plane
	shared_ptr<HelperShader> planeShader;
	unique_ptr<MeshRenderer> planeMesh;
	shared_ptr<Material> planeMaterial;

	bool isDirty;
	//Input
	bool enableCameraMovement;
	bool enableLightMovement;

	glm::vec3 eye_pos;
	glm::vec3 light_pos;
	MyCamera* mainCamera;
	glm::vec3 target_pos;
};
