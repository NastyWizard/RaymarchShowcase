#include "TestScene.h"
#include <memory>

TestScene::TestScene() : Scene("TestScene")
{
	Material* mat = new Material(new Shader("Shaders/default.vert", "Shaders/default.frag"));
	Mesh* mesh = new Mesh();
	mesh->SetMesh(Mesh::RECT);
	testObj = new Object("test",mat,mesh);
	AddChild(testObj);
}

TestScene::~TestScene()
{
	delete testObj;
}

void TestScene::Update()
{
	Scene::Update();
}

void TestScene::Render()
{
	Scene::Render();
}
