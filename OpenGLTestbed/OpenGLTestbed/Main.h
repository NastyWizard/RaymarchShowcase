#pragma once
#include "Material.h"
#include "SceneManager.h"
#include <glad\glad.h>
#include <GLFW\glfw3.h>

SceneManager* SceneManager::instance = 0;

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow *window);
void InitScenes();
void Update();
void RenderScreen();
void ClearScreen();
//class Main 
//{
//};