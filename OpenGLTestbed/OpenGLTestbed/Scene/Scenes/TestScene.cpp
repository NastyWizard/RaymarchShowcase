#include "TestScene.h"
#include "Time.h"
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
	ShowObjectMenu(testObj);
}

void TestScene::Render()
{
	Scene::Render();
}

void TestScene::ShowObjectMenu(Object* o) 
{
	std::string str = "Object : " + o->GetName();
	ImGui::Begin(str.c_str());
	{
		ImGui::Text(o->GetMaterial()->GetShader()->GetVertex().c_str());
		ImGui::Text(o->GetMaterial()->GetShader()->GetFragment().c_str());

		ImGui::Spacing();

		static int fragSelection;
		static int vertSelection;
		ImGui::Combo("Vertex Shader", &vertSelection, "default.vert\0\0");
		ImGui::Combo("Fragment Shader", &fragSelection, "default.frag\0RayTest.frag\0");

		if (ImGui::Button("Set Shader"))
		{
			std::string vert;
			std::string frag;
			/////////////////////////
			switch (vertSelection)
			{
			case 0:
				vert = "Shaders/default.vert";
				break;
			default:
				break;
			}
			///////////////////////// 
			switch (fragSelection)
			{
			case 0:
				frag = "Shaders/default.frag";
				break;
			case 1:
				frag = "Shaders/RayTest.frag";
				break;
			default:
				break;
			}

			o->GetMaterial()->SetShader(new Shader(vert, frag));

		}

		ImGui::Separator();

		if (ImGui::TreeNode("Uniforms"))
		{
			ImGui::Text("Global");

			ImGui::Separator();

			ImGui::Text("Unique");


			ImGui::Separator();
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Transform"))
		{
			ImGui::Text("Position");
			ImGui::SliderFloat("pX", &o->transform.position.x, -2.f, 2.f);
			ImGui::SliderFloat("pY", &o->transform.position.y, -2.f, 2.f);
			ImGui::SliderFloat("pZ", &o->transform.position.z, -2.f, 2.f);

			ImGui::Separator();

			ImGui::Text("Rotation");
			static float a;
			ImGui::SliderFloat("Angle", &a, -1.f, 1.f);
			o->transform.rotation.w = abs(a);
			ImGui::SliderFloat("rX", &o->transform.rotation.v.x, 0.f, 1.f);
			ImGui::SliderFloat("rY", &o->transform.rotation.v.y, 0.f, 1.f);
			ImGui::SliderFloat("rZ", &o->transform.rotation.v.z, 0.f, 1.f);

			ImGui::Separator();

			ImGui::Text("Scale");
			ImGui::SliderFloat("sX", &o->transform.scale.x, 0.f, 2.f);
			ImGui::SliderFloat("sY", &o->transform.scale.y, 0.f, 2.f);
			ImGui::SliderFloat("sZ", &o->transform.scale.z, 0.f, 2.f);
			ImGui::Separator();
			ImGui::TreePop();
		}
	}
	ImGui::End();
}