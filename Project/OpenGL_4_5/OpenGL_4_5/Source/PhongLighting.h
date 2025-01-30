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
	void UpdateInput(char x, int y, int z);
	void UpdateButtonUp(char x);
	void UpdateMouseInput(int dx, int dy, bool bIsMouseLBDown);
	void printDebugInfo();
	
	HelperShader* phongShader;

	MeshRenderer* cubeMesh;
	Material* phongMaterial;

	glm::vec3 eye_pos;
	glm::vec3 light_pos;
	MyCamera* mainCamera;
	glm::vec3 target_pos;

	//Lamp Mesh
	HelperShader* lampShader;
	MeshRenderer* lampMesh;
	Material* lampMaterial;
	//Plane
	HelperShader* planeShader;
	MeshRenderer* planeMesh;
	Material* planeMaterial;

	//Input
	bool enableCameraMovement;
	bool enableLightMovement;

};

