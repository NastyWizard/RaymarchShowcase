#include "TestScene.h"
#include "Time.h"
#include "../../Graphics/UIHelpers.h"
#include <memory>

TestScene::TestScene() : Scene("TestScene")
{
	// initialize objects and materials
	Material* mat = new Material(new Shader("Shaders/default.vert", "Shaders/RayTest.frag"));

	testTex = new Texture("Textures/checker.png", GL_NEAREST_MIPMAP_NEAREST,GL_NEAREST);
	testTex2 = new Texture("Textures/test.png");

	Mesh* mesh = new Mesh();
	mesh->SetMesh(Mesh::RECT);
	testObj = new Object("test",mat,mesh);
	testObj->transform.position = vec3(0.f, 0.f, 0.f);
	testObj->transform.scale = vec3(1.f);
	testObj->transform.rotation.SetAngleAxis(DegToRad(0.f), vec3::UnitZ());

	testObj->GetMaterial()->AddUniformSampler2D("MainTex", testTex);
	testObj->GetMaterial()->AddUniformSampler2D("MainTex2", testTex2);

	testObj->GetMaterial()->AddUniformInt("Debug", 0);
	testObj->GetMaterial()->AddUniformInt("MaxSteps", 512);

	testObj->GetMaterial()->AddUniformFloat3("SpherePos", 0.f, 0.f, 0.f);

	testObj->GetMaterial()->AddUniformColor("SphereColor", 1.f, 1.f, 1.f, 1.f);
	testObj->GetMaterial()->AddUniformColor("GroundColor", 1.f, .35f, .35f, 1.f);
	testObj->GetMaterial()->AddUniformColor("FogColor", 0.2f, .35f, .8f, 1.f);


	testObj->GetMaterial()->AddUniformFloat2("NoiseScale", .25f,.25f);

	testObj->GetMaterial()->AddUniformFloat("MinFogDist", 40.f);
	testObj->GetMaterial()->AddUniformFloat("MaxFogDist", 60.f);
	testObj->GetMaterial()->AddUniformFloat("NoiseYBoost", 2.f);
	
	// TODO: Make XML save and load for uniform values

	ShowOverlay = true;
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
	ImGui::ShowDemoWindow();

	if(ShowOverlay)
		ShowPerformanceOverlay(&ShowOverlay);
	ShowObjectMenu(testObj);

	if (testObj->GetMaterial()->GetUniformFloat("MinFogDist") >= testObj->GetMaterial()->GetUniformFloat("MaxFogDist"))
		testObj->GetMaterial()->SetUniformFloat("MinFogDist", testObj->GetMaterial()->GetUniformFloat("MaxFogDist") - 1.f);

}

void TestScene::Render()
{
	Scene::Render();
}