#include "Window.h"

// default window size
int Window::width = 800;
int Window::height = 600;
GLFWwindow *Window::window = nullptr;

void Window::Close()
{
	glfwSetWindowShouldClose(window, true);
}
