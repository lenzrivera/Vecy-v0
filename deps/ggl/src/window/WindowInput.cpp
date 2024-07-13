#include "WindowInput.h"

using namespace ggl;

WindowInput::WindowInput() : 
	currCursorPosition(0.0),
	lastCursorPosition(currCursorPosition), 
	inputStates()
{
}

// Input Information //

glm::dvec2 WindowInput::getCursorMovementOffset() const
{
	return currCursorPosition - lastCursorPosition;
}

glm::dvec2 WindowInput::getCursorPosition() const
{
	return currCursorPosition;
}

// Input State //

bool WindowInput::isHeld(InputCode keyCode) const
{
	return inputStates[keyCode].isHeld;
}

bool WindowInput::isPressed(InputCode keyCode) const
{
	const InputState& inputState = inputStates[keyCode];
	return inputState.isHeld && inputState.hasNotBeenPressed;
}

bool WindowInput::isReleased(InputCode keyCode) const
{
	const InputState& inputState = inputStates[keyCode];
	return !inputState.isHeld && inputState.hasNotBeenReleased;
}

bool WindowInput::mouseDragged(MouseButton mouseButton) const
{
	return isHeld(mouseButton) && getCursorMovementOffset() != glm::dvec2(0.0);
}

// Application Loop Methods //

void WindowInput::pollInputs(GLFWwindow* assignedWindow, HWND assignedWindowHandle)
{
	// note issue
	if (GetActiveWindow() != assignedWindowHandle)
		return;

	lastCursorPosition = currCursorPosition;
	glfwGetCursorPos(assignedWindow, &currCursorPosition.x, &currCursorPosition.y);


	for (InputCode i = FIRST_INPUT_CODE_INDEX; i < LAST_INPUT_CODE_INDEX; i++)
	{
		if (isPressed(i))
		{
			inputStates[i].hasNotBeenPressed = false;
			inputStates[i].hasNotBeenReleased = true;
		}
		
		if (isReleased(i))
		{
			inputStates[i].hasNotBeenReleased = false;
			inputStates[i].hasNotBeenPressed = true;
		}

		inputStates[i].isHeld = getInputHeldState(i);
	}
}