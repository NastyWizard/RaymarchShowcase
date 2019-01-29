#include "Main.h"
#include "Util\Helpers.h"
#include "Scene\Scenes\TestScene.h"
#include "Util\Time.h"
#include "Util\Window.h"
#include "Graphics\UIHelpers.h"
#include "Libraries\imgui/imgui.h"
#include "Libraries\imgui/imgui_impl_glfw.h"
#include "Libraries\imgui/imgui_impl_opengl3.h"
#include <iostream>
#include <memory>

//
int main() 
{

	// initialize glfw
	if (!glfwInit()) return 1;

	const char* glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
	glfwWindowHint(GLFW_DECORATED, false);
	// initialize window
	GLFWwindow* window = glfwCreateWindow(Window::width, Window::height, "Testbed v1.0", nullptr, nullptr);
	if (window == nullptr) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	Window::window = window;

	const HWND desktopWindow = GetDesktopWindow();
	RECT res;
	res.right = GetSystemMetrics(SM_CXSCREEN);
	res.bottom = GetSystemMetrics(SM_CYSCREEN);

	glfwSetWindowPos(window,(res.right/2) - Window::width / 2, (res.bottom/2) - Window::height/ 2);

	glfwMakeContextCurrent(window); 
	glfwSwapInterval(1); // vsync

	// initialize GLAD
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);


	// custom style
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.42f, 0.42f, 0.42f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.53f, 0.53f, 0.53f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.42f, 0.42f, 0.42f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.42f, 0.42f, 0.42f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.67f, 0.67f, 0.67f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.23f, 0.23f, 0.23f, 1.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.70f, 0.70f, 0.70f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.42f, 0.42f, 0.42f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.40f, 0.40f, 0.40f, 0.50f);
	colors[ImGuiCol_Tab] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.67f, 0.70f, 0.72f, 1.00f);
	colors[ImGuiCol_TabActive] = ImVec4(0.42f, 0.42f, 0.42f, 1.00f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 0.51f, 0.29f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 0.51f, 0.29f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 0.59f, 0.41f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(1.00f, 0.51f, 0.29f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(1.00f, 0.71f, 0.58f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(1.00f, 0.74f, 0.40f, 1.00f);




	InitScenes();

	while (!glfwWindowShouldClose(window))
	{

		// process input
		ProcessInput(window);
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ShowMenuBar();

		// update
		Update();
		// render
		RenderScreen();

		// Rendering ImGui
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwMakeContextCurrent(window);
		// swap buffers
		glfwSwapBuffers(window);
	}

	delete SceneManager::GetInstance();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
	
	return 0;
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	Window::width = width;
	Window::height = height;
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void InitScenes()
{
	TestScene* scene1 = new TestScene();
	SceneManager::AddScene(scene1);
}

void Update() 
{
	if(SceneManager::GetCurrentScene())
		SceneManager::GetCurrentScene()->Update();
}

void RenderScreen() 
{
	ClearScreen();
	if (SceneManager::GetCurrentScene())
		SceneManager::GetCurrentScene()->Render();
}

void ClearScreen()
{
	// clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//glClearColor(0.0f, .6f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}