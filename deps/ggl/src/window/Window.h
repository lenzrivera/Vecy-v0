#ifndef WINDOW_MAIN_H
#define WINDOW_MAIN_H

// Required to prevent redefinition of APIENTRY
#include <Windows.h> 

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "WindowInput.h"

namespace ggl
{

	class Window
	{
	private:
		GLFWwindow* window;
		HWND windowHandle;

		int m_width, m_height;

		mutable WindowInput m_input;

	public:
		Window() = delete;
		Window(int width, int height, const char* title, bool resizable = false);
		~Window();

		// Getters //

		GLFWwindow* handle() const;

		int width() const;
		int height() const;

		const WindowInput& input() const;

		// Window Manipulation //

		void close() const;

		// Window State //

		bool shouldClose() const;

		void pollEvents() const;
		void swapBuffers() const;
	};

}

#endif