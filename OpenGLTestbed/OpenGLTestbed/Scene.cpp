#include "Scene.h"

Scene::Scene(std::string Name) : SceneNode(Name)
{

}

Scene::~Scene()
{
}

void Scene::Init()
{
	SceneNode::Init();
}

void Scene::Update()
{
	SceneNode::Update();
}

void Scene::Render()
{
	SceneNode::Render();
}
