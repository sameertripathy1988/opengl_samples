#pragma once
#include "Material.h"
#include <glm/glm/gtc/matrix_transform.hpp> 
#include "glm\glm\glm.hpp"

enum MESH_TYPE
{
	PLANE,
	CUBE,
	MODEL,
	LINE
};
class MeshRenderer
{
public:
	MeshRenderer();
	~MeshRenderer();
	void render();
	void render(shared_ptr<HelperShader> shader); //Use explicit shader to render the objects
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
	
	void setLineInfo(const glm::vec3& line1, const glm::vec3& line2, const GLfloat width = 2.0f);

private:
	shared_ptr<Material> material;
	MESH_TYPE meshType;

	// Transformation variables
	glm::vec3 translation;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::vec3 point1;
	glm::vec3 point2;
	GLfloat lineWidth;

	GLuint model_vbo;
	GLuint model_vao;
	GLuint ebo;

	void createPlane();
	void createCube();
	void createModel();
	void createLine();

	void renderPlane();
	void renderCube();
	void renderModel();
	void renderLine();	
};

