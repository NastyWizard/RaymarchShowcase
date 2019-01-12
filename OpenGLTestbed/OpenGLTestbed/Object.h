#pragma once
#include "SceneNode.h"
#include "Material.h"
#include "Mesh.h"
#include "Transform.h"

class Object : public SceneNode
{
	//variables
private:
	Material* material;
	Mesh* mesh;
public:

	// functions
private:
public:

	Object(std::string name);
	Object(std::string name, Material* mat, Mesh* mesh);
	~Object();

	void SetMaterial(Material* mat);
	Material* GetMaterial();

	void SetMesh(Mesh* mesh);
	Mesh* GetMesh();

	void Init();
	void Update();
	void Render();
};