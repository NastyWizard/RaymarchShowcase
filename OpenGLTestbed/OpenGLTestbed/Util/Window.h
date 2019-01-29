#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>
class Window
{
public:

	static int width;
	static int height;

	static GLFWwindow *window;

	static void Close();
private:

};