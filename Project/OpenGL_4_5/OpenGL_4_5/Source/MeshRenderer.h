#pragma once
#include "Material.h"
#include <glm/glm/gtc/matrix_transform.hpp> 
#include "glm\glm\glm.hpp"

enum MESH_TYPE
{
	PLANE,
	CUBE,
	MODEL
};
class MeshRenderer
{
public:
	MeshRenderer();
	~MeshRenderer();
	void render();
	void create(const MESH_TYPE& meshType);
	void setMaterial(const shared_ptr<Material>& material_);
	shared_ptr<Material> getMaterial() { return material; }

	// Setters and getters for transformation variables
	void setTranslation(const glm::vec3& translation_);
	glm::vec3 getTranslation() const;
	void setRotation(const glm::vec3& rotation_);
	glm::vec3 getRotation() const;
	void setScale(const glm::vec3& scale_);
	glm::vec3 getScale() const;

	// Method to calculate the model matrix
	glm::mat4 getModelMatrix() const;

private:
	shared_ptr<Material> material;
	MESH_TYPE meshType;

	// Transformation variables
	glm::vec3 translation;
	glm::vec3 rotation;
	glm::vec3 scale;

	GLuint model_vbo;
	GLuint model_vao;
	GLuint ebo;

	void createPlane();
	void createCube();
	void createModel();

	void renderPlane();
	void renderCube();
	void renderModel();
};

