#include "Main.h"
#include "Util\Helpers.h"
#include "Scene\Scenes\TestScene.h"
#include "Util\Time.h"
#include "Util\Window.h"
#include "Libraries/imgui/imgui.h"
#include "Libraries/imgui/imgui_impl_glfw.h"
#include "Libraries/imgui/imgui_impl_opengl3.h"
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

	// initialize window
	GLFWwindow* window = glfwCreateWindow(Window::width, Window::height, "Testbed v1.0", nullptr, nullptr);
	if (window == nullptr) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
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

	InitScenes();

	while (!glfwWindowShouldClose(window))
	{

		// process input
		ProcessInput(window);
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
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
	glClearColor(0.0f, .6f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}