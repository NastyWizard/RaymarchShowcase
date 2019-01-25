#include "Scene.h"

Scene::Scene(std::string Name) : SceneNode(Name)
{

}

Scene::~Scene()
{
	SceneNode::~SceneNode();
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
