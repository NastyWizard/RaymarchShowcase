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

	// TODO: add options for filter mode / wrap mode / vertical flip
	testObj->GetMaterial()->AddUniformSampler2D("MainTex", testTex);
	testObj->GetMaterial()->AddUniformSampler2D("MainTex2", testTex2);

	testObj->GetMaterial()->AddUniformInt("Debug", 0);
	testObj->GetMaterial()->AddUniformInt("MaxSteps", 512);
	testObj->GetMaterial()->AddUniformInt("FractalIterations", 3);

	testObj->GetMaterial()->AddUniformFloat3("CameraPos", 0.f, 3.f, 10.f); 

	testObj->GetMaterial()->AddUniformColor("SphereColor", .9f, .78f, .64f, 1.f);
	testObj->GetMaterial()->AddUniformColor("GroundColor", .69f, .78f, .8f, 1.f);
	testObj->GetMaterial()->AddUniformColor("FogColor", 0.34f, .59f, .91f, 1.f);

	testObj->GetMaterial()->AddUniformFloat("MinFogDist", 2.f);
	testObj->GetMaterial()->AddUniformFloat("MaxFogDist", 25.f);
	
	// TODO: Make XML save and load for uniform values

    ShowOverlay = true;
    ShowDemoMenu = false;
	ShowAnyMenu = true;
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

    ShowMenuBar(&ShowAnyMenu, &ShowDemoMenu);

	if (ShowAnyMenu)
	{
		if (ShowDemoMenu)
			ImGui::ShowDemoWindow();

		if (ShowOverlay)
			ShowPerformanceOverlay(&ShowOverlay);
		ShowObjectMenu(testObj);
	}

	if (testObj->GetMaterial()->GetUniformFloat("MinFogDist") >= testObj->GetMaterial()->GetUniformFloat("MaxFogDist"))
		testObj->GetMaterial()->SetUniformFloat("MinFogDist", testObj->GetMaterial()->GetUniformFloat("MaxFogDist") - 1.f);

}

void TestScene::Render()
{
	Scene::Render();
}