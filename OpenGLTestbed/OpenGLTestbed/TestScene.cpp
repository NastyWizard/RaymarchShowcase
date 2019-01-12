#include "TestScene.h"
#include <memory>

TestScene::TestScene() : Scene("TestScene")
{
	Material* mat = new Material(new Shader("Shaders/default.vert", "Shaders/default.frag"));

	testTex = new Texture("Textures/checker.png", GL_NEAREST_MIPMAP_NEAREST,GL_NEAREST);
	testTex2 = new Texture("Textures/test.png");

	Mesh* mesh = new Mesh();
	mesh->SetMesh(Mesh::RECT);
	testObj = new Object("test",mat,mesh);
	testObj->transform.position = vec3(0.0f, 0.0f, 0.0f);
	AddChild(testObj);
}

TestScene::~TestScene()
{
	Scene::~Scene();
	delete testTex;
	delete testTex2;
}

void TestScene::Update()
{
	Scene::Update();
}

void TestScene::Render()
{
	//testObj->GetMaterial()->SetUniformSampler2D_s(0, "MainTex",testTex);
	//testObj->GetMaterial()->SetUniformSampler2D_s(1, "MainTex2",testTex2);
	Scene::Render();
	testObj->GetMaterial()->SetUniformSampler2D("MainTex", testTex);
	testObj->GetMaterial()->SetUniformSampler2D("MainTex2", testTex2);
}
