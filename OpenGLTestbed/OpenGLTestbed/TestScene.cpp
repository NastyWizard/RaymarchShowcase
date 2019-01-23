#include "TestScene.h"
#include "Time.h"
#include <memory>

TestScene::TestScene() : Scene("TestScene")
{
	Material* mat = new Material(new Shader("Shaders/default.vert", "Shaders/RayTest.frag"));

	testTex = new Texture("Textures/checker.png", GL_NEAREST_MIPMAP_NEAREST,GL_NEAREST);
	testTex2 = new Texture("Textures/test.png");

	Mesh* mesh = new Mesh();
	mesh->SetMesh(Mesh::RECT);
	testObj = new Object("test",mat,mesh);
	testObj->transform.position = vec3(0.f, 0.f, 0.f);
	//testObj->transform.rotation.SetAngleAxis(DegToRad(90.f), vec3::UnitX());
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
	float t = Time::GetTime() * .000005f;
	//testObj->transform.position = vec3::UnitY()*10.f*(sinf(t) + 1.f);
	//testObj->transform.rotation.SetAngleAxis((sinf(t) + 1.f) * 180.f, vec3::UnitY());
}

void TestScene::Render()
{
	//testObj->GetMaterial()->SetUniformSampler2D_s(0, "MainTex",testTex);
	//testObj->GetMaterial()->SetUniformSampler2D_s(1, "MainTex2",testTex2);
	Scene::Render();
	testObj->GetMaterial()->SetUniformSampler2D("MainTex", testTex);
	testObj->GetMaterial()->SetUniformSampler2D("MainTex2", testTex2);
}
