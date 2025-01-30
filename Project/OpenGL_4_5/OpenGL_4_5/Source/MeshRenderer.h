#pragma once
#include "Material.h"

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
	void render(MESH_TYPE meshType);
	void create(MESH_TYPE meshType);
	void setMaterial(Material*& material_);
private:
	Material* material;
	//Cube
	GLuint cube_vbo;
	GLuint cube_vao;

	//Plane
	GLuint plane_vbo;
	GLuint plane_vao;

	void createPlane();
	void createCube();
	void createModel();

	void renderPlane();
	void renderCube();
	void renderModel();
};

