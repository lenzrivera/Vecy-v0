#ifndef WINDOW_INPUT_H
#define WINDOW_INPUT_H

#include <Windows.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "InputState.h"
#include "KeyCodes.h"

namespace ggl {

	class WindowInput
	{
	private:
		glm::dvec2 currCursorPosition;
		glm::dvec2 lastCursorPosition;

		InputState inputStates[LAST_INPUT_CODE_INDEX];

		// Application Loop Methods //

		friend class Window;
		WindowInput();
		void pollInputs(GLFWwindow* assignedWindow, HWND assignedWindowHandle);

	public:
		// Input Information //

		glm::dvec2 getCursorMovementOffset() const;
		glm::dvec2 getCursorPosition() const;

		// Input State //

		bool isHeld(InputCode keyCode) const;
		bool isPressed(InputCode keyCode) const;
		bool isReleased(InputCode keyCode) const;

		bool mouseDragged(MouseButton mouseButton) const;
	};
	
}

#endif