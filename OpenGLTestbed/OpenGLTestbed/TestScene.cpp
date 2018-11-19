#include "TestScene.h"
#include <memory>

TestScene::TestScene() : Scene("TestScene")
{
	Material* mat = new Material(new Shader("Shaders/default.vert", "Shaders/default.frag"));
	
	testTex = new Texture("Textures/test.jpg");

	Mesh* mesh = new Mesh();
	mesh->SetMesh(Mesh::RECT);
	testObj = new Object("test",mat,mesh);
	AddChild(testObj);
}

TestScene::~TestScene()
{
	Scene::~Scene();
	delete testTex;
}

void TestScene::Update()
{
	Scene::Update();
}

void TestScene::Render()
{
	Scene::Render();
	testObj->GetMaterial()->SetUniformSampler2D("texture", testTex);
}
