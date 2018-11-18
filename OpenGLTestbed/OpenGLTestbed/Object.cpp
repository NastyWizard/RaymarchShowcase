#include "Object.h"

void Object::Update()
{
	SceneNode::Update();
}

void Object::Render()
{
	SceneNode::Render();
	material->UseShader();
	mesh->Draw();
}
