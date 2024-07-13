#include "Window.h"

#include <iostream>

#include <cassert>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

using namespace ggl;

Window::Window(
	int width, int height, const char* title, bool resizable) : 
	window(nullptr), 
	windowHandle(nullptr), 

	m_width(width), 
	m_height(height), 

	m_input()
{
	std::cout << glfwInit() << std::endl;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, resizable);

	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	windowHandle = glfwGetWin32Window(window);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	std::cout << glewInit();
}

Window::~Window()
{
	glfwTerminate();
}

// Getters //

GLFWwindow* Window::handle() const
{
	return window;
}

int Window::width() const
{
	return m_width;
}

int Window::height() const
{
	return m_height;
}

const WindowInput& Window::input() const
{
	return m_input;
}

// Window Manipulation //

void Window::close() const
{
	glfwSetWindowShouldClose(window, GL_TRUE);
}


// Window State //

bool Window::shouldClose() const
{
	return glfwWindowShouldClose(window);
}

void Window::pollEvents() const
{
	glfwPollEvents();
	m_input.pollInputs(window, windowHandle);
}

void Window::swapBuffers() const
{
	glfwSwapBuffers(window);
}