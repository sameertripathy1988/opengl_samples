#pragma once
#include "BlankTest.h"
#include "MeshRenderer.h"
#include "HelperShader.h"
#include "MyCamera.h"
#include <vector>
using namespace std;

class CascadedShadowMapping : public BlankTest
{
public:
	CascadedShadowMapping();
	~CascadedShadowMapping();

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

	GLuint tex_crate_diffuse;
	GLuint tex_crate_normal;

	GLuint tex_brick_diffuse;
	GLuint tex_brick_normal;

	//CSM
	vector<GLuint> shadowMapFBOs;
	vector<GLuint> shadowMaps;
	vector<glm::mat4> lightViewMatrices;
	vector<glm::mat4> lightProjMatrices;
	vector<float> cascadeSplits;

	void createShadowMapFBOs();
	void calculateCascadeSplits();
	void calculateLightMatrices(const glm::mat4 viewMatrix, const glm::mat4 projMatrix);

};