#include "Main.h"
#include "Helpers.h"
#include "TestScene.h"
#include <iostream>
#include <memory>


int main() 
{
	// initialize glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// initialize window
	GLFWwindow* window = glfwCreateWindow(800, 600, "Testbed v1.0", nullptr, nullptr);
	if (window == nullptr) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// initialize GLAD
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	InitScenes();

	while (!glfwWindowShouldClose(window))
	{
		// process input
		ProcessInput(window);

		// update
		Update();

		// render
		RenderScreen();

		// swap buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	delete SceneManager::GetInstance();
	glfwTerminate();
	
	return 0;
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
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