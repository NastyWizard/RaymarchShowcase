#pragma once
#include "SceneNode.h"
#include "Material.h"
#include "Mesh.h"

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

	void Update();
	void Render();
};