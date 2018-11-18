#include "Scene.h"

Scene::Scene(std::string Name) : SceneNode(Name)
{

}

Scene::~Scene()
{
}

void Scene::Update()
{
	SceneNode::Update();
}

void Scene::Render()
{
	SceneNode::Render();
}
