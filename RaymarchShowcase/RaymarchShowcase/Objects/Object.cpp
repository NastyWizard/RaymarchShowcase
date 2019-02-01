#include "Object.h"

Object::Object(std::string name) : SceneNode(name)
{
}

Object::Object(std::string name, Material * mat, Mesh * mesh) : SceneNode(name)
{
	material = mat;
	this->mesh = mesh;
}

Object::~Object()
{
	if (material != nullptr)
	{
		delete material;
		material = nullptr;
	}

	if (mesh != nullptr)
	{
		delete mesh;
		mesh = nullptr;
	}
}

void Object::SetMaterial(Material * mat)
{
	material = mat;
}

Material * Object::GetMaterial()
{
	return material;
}

void Object::SetMesh(Mesh * mesh)
{
	this->mesh = mesh;
}

Mesh * Object::GetMesh()
{
	return mesh;
}

void Object::Init()
{
	SceneNode::Init();
}

void Object::Update()
{
	SceneNode::Update();
}

void Object::Render()
{
	SceneNode::Render();

	if (material != nullptr && mesh != nullptr)
	{
		material->UseShader();
		material->SetUniformMatrix4x4("ObjectMatrix", transform.GetMatrix());

		material->UpdateGlobalUniforms();
		material->UpdateUniqueUniforms();
		mesh->Draw();
	}
}
