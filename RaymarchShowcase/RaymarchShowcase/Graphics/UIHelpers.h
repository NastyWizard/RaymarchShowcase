#pragma once
#include "../Objects/Object.h"
#include "../Libraries/imgui/imgui.h"
#include "../Util/Window.h"
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <algorithm>

static bool dragging;

inline static void ShowMenuBar(bool* ShowAnyMenu, bool* ShowDemoMenu)
{
	if (ImGui::BeginMainMenuBar()) 
	{
		//int x, y;
		//
		//if (ImGui::GetMousePos().y < 20)
		//{
		//	if (ImGui::IsMouseClicked(0))
		//		dragging = true;
		//}
        //
		//if (dragging)
		//{
		//	glfwGetWindowPos(Window::window, &x, &y);
        //
		//	ImVec2 deltaPos = ImGui::GetMouseDragDelta();
        //
		//	glfwSetWindowPos(Window::window, x + deltaPos.x, y + deltaPos.y);
		//}
        //
		//if (!ImGui::IsMouseDown(0)) dragging = false;


		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Close")) 
			{
				Window::Close();
			}
			ImGui::EndMenu();
		}

		ImGui::Separator();

        if (ImGui::BeginMenu("Edit"))
        {

            ImGui::EndMenu();
        }

		ImGui::Separator();
        if (ImGui::BeginMenu("View"))
        {
			if (ImGui::MenuItem("Show/Hide All"))
				*ShowAnyMenu = !*ShowAnyMenu;

            if (ImGui::MenuItem("Demo Menu")) 
                *ShowDemoMenu = !*ShowDemoMenu;

            ImGui::EndMenu();
        }

		ImGui::Separator();

		//if(ImGui::Button("Close")) 
		//{
		//	Window::Close();
		//}

		ImGui::EndMainMenuBar();
	}
}

inline static void ShowPerformanceOverlay(bool* p_open)
{
	const float DISTANCE = 20.0f;
	static int corner = 0;
	ImVec2 window_pos = ImVec2((corner & 1) ? ImGui::GetIO().DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? ImGui::GetIO().DisplaySize.y - DISTANCE : DISTANCE);
	ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
	if (corner != -1)
		ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
	ImGui::SetNextWindowBgAlpha(0.3f); // Transparent background
	if (ImGui::Begin("Example: Simple overlay", p_open, (corner != -1 ? ImGuiWindowFlags_NoMove : 0) | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::Separator();
		if (ImGui::IsMousePosValid())
			ImGui::Text("Mouse Position: (%.1f,%.1f)", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
		else
			ImGui::Text("Mouse Position: <invalid>");
		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::MenuItem("Custom", NULL, corner == -1)) corner = -1;
			if (ImGui::MenuItem("Top-left", NULL, corner == 0)) corner = 0;
			if (ImGui::MenuItem("Top-right", NULL, corner == 1)) corner = 1;
			if (ImGui::MenuItem("Bottom-left", NULL, corner == 2)) corner = 2;
			if (ImGui::MenuItem("Bottom-right", NULL, corner == 3)) corner = 3;
			if (p_open && ImGui::MenuItem("Close")) *p_open = false;
			ImGui::EndPopup();
		}
	}
	ImGui::End();
}


////////////////////////////////////////////////////

inline void ShowObjectMenu(Object* o)
{
	std::string str = "Object : " + o->GetName();
	ImGui::Begin(str.c_str(), false, ImGuiWindowFlags_AlwaysAutoResize);
	{
		if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
		{
			if (ImGui::BeginTabItem("Shader"))
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
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Uniforms"))
			{

				ImGui::Text("Global");

				ImGui::Separator();

				ImGui::Text("Unique");

				// UNIFORM DRAWING

				// these are used to help with separating the different types
				bool doingSampler2D = false;
				bool doingMatrix = false;
				bool doingInt = false;
				bool doingFloat = false;
				bool doingFloat2 = false;
				bool doingFloat3 = false;
				bool doingFloat4 = false;
				bool doingColor = false;

				std::map<std::string, Material::UniformType>::iterator it2 = o->GetMaterial()->Uniforms.begin();

				// super inefficient probably

				// Sorting by value, so all sections are displayed together.
				auto flippedUniformMap = MapToVec(o->GetMaterial()->Uniforms);

				struct compareOp
				{
					inline bool operator() (const std::pair<std::string, Material::UniformType> a, const std::pair<std::string, Material::UniformType> b)
					{
						return a.second < b.second;
					}
				};
				std::sort(flippedUniformMap.begin(), flippedUniformMap.end(), compareOp());
				//////////////////////////--------------------------------//////////////////////////
				//////////////////////////--------------------------------//////////////////////////

				for (int i = 0; i < (int)flippedUniformMap.size(); i++)
				{
					std::string loc = flippedUniformMap[i].first;
					Material::UniformType type = flippedUniformMap[i].second;
					std::string label;

					int in;
					float f;
					float fa2[2];
					float fa3[3];
					float fa4[4];
					float2 f2;
					float3 f3;
					float4 f4;

					switch (type)
					{
					case Material::UniformType::SAMPLER2D:
						if (!doingSampler2D)
						{
							ImGui::Separator();
							doingSampler2D = true;
						}

						label = "\tTexture: " + o->GetMaterial()->GetUniformSampler2D(loc)->GetLocation();
						ImGui::Text(label.c_str());

						break;
					case Material::UniformType::MAT4X4:

						if (!doingMatrix)
						{
							ImGui::Separator();
							doingMatrix = true;
						}


						label = "\tMatrix4x4: " + loc;
						ImGui::Text(label.c_str());

						break;
					case Material::UniformType::INT:

						if (!doingInt)
						{
							ImGui::Separator();
							doingInt = true;
						}


						label = "\tInteger: " + loc;

						in = o->GetMaterial()->GetUniformInt(loc);
						if (ImGui::DragInt(label.c_str(), &in, .1f))
							o->GetMaterial()->SetUniformInt(loc, in);

						break;
					case Material::UniformType::FLOAT:

						if (!doingFloat)
						{
							ImGui::Separator();
							doingFloat = true;
						}


						label = "\tFloat: " + loc;
						f = o->GetMaterial()->GetUniformFloat(loc);
						if (ImGui::DragFloat(label.c_str(), &f, .1f))
							o->GetMaterial()->SetUniformFloat(loc, f);

						break;
					case Material::UniformType::FLOAT2:

						if (!doingFloat2)
						{
							ImGui::Separator();
							doingFloat2 = true;
						}


						label = "\tFloat2: " + loc;
						f2 = o->GetMaterial()->GetUniformFloat2(loc);
						fa2[0] = f2.x; fa2[1] = f2.y;
						if (ImGui::DragFloat2(label.c_str(), fa2, .1f))
						{
							f2.x = fa2[0]; f2.y = fa2[1];
							o->GetMaterial()->SetUniformFloat2(loc, f2);
						}

						break;
					case Material::UniformType::FLOAT3:

						if (!doingFloat3)
						{
							ImGui::Separator();
							doingFloat3 = true;

						}


						label = "\tFloat3: " + loc;
						f3 = o->GetMaterial()->GetUniformFloat3(loc);
						fa3[0] = f3.x; fa3[1] = f3.y; fa3[2] = f3.z;
						if (ImGui::DragFloat3(label.c_str(), fa3, .1f))
						{
							f3.x = fa3[0]; f3.y = fa3[1]; f3.z = fa3[2];
							o->GetMaterial()->SetUniformFloat3(loc, f3);
						}

						break;
					case Material::UniformType::FLOAT4:

						if (!doingFloat4)
						{
							ImGui::Separator();
							doingFloat4 = true;
						}


						label = "\tFloat4: " + loc;
						f4 = o->GetMaterial()->GetUniformFloat4(loc);
						fa4[0] = f4.x; fa4[1] = f4.y; fa4[2] = f4.z;
						if (ImGui::DragFloat4(label.c_str(), fa4, .1f))
						{
							f4.x = fa4[0]; f4.y = fa4[1]; f4.z = fa4[2];
							o->GetMaterial()->SetUniformFloat4(loc, f4);
						}

						break;
					case Material::UniformType::COLOR:

						if (!doingFloat4)
						{
							ImGui::Separator();
							doingFloat4 = true;
						}


						label = "\tColor: " + loc;
						f4 = o->GetMaterial()->GetUniformFloat4(loc);
						fa4[0] = f4.x; fa4[1] = f4.y; fa4[2] = f4.z; fa4[3] = f4.w;
						if (ImGui::ColorEdit4(label.c_str(), fa4))
						{
							f4.x = fa4[0]; f4.y = fa4[1]; f4.z = fa4[2]; f4.w = fa4[3];
							o->GetMaterial()->SetUniformFloat4(loc, f4);
						}

						break;
					default:
						break;
					}

				}

				//////////////////////////--------------------------------//////////////////////////
				//////////////////////////--------------------------------//////////////////////////

				ImGui::Separator();
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Transform"))
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
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
	}
	ImGui::End();
}