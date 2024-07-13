#include "VecyMain.h"

#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL

#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#include "vectors/Vector.h"
#include "vectors/VectorBounds.h"

static const double KEYBOARD_INPUT_OFFSET_VELOCITY = 500.0;

VecyMain::VecyMain(const ggl::Window& window) : 
	hoveredVector(-1),
	noVectorSelection(true),

	/* Both these members could be omitted for something better, idk though. */
	gridInputOngoing(false),
	vectorInputOngoing(false),

	needsRender(true),
	centerOffset(0.0), 
	projection(glm::ortho<double>(
		-window.width(), window.width(), -window.height(), window.height())),

	grid(window.width(), window.height(), projection),
	vectors(grid.getUnitDistance(), projection)
{
}

// Input Management //

/* `dt` is mostly ignored. */
/* Same comment on `gridInputOngoing` and `vectorInputOngoing`. What a mess. */

void VecyMain::handleGridNavigation(const ggl::Window& window, double dt)
{
	bool inputOngoing = false;
	
	// Keyboard Input //

	double keyboardOffset = KEYBOARD_INPUT_OFFSET_VELOCITY * dt;

	if (window.input().isHeld(ggl::Key::W))
	{
		centerOffset.y -= keyboardOffset;
		inputOngoing = true;
		needsRender = true;
	}
	else if (window.input().isReleased(ggl::Key::W))
	{
		inputOngoing ^= false;
		needsRender = true;
	}

	if (window.input().isHeld(ggl::Key::S))
	{
		centerOffset.y += keyboardOffset;
		inputOngoing = true;
		needsRender = true;
	}
	else if (window.input().isReleased(ggl::Key::S))
	{
		inputOngoing ^= false;
		needsRender = true;
	}

	if (window.input().isHeld(ggl::Key::A))
	{
		centerOffset.x += keyboardOffset;
		inputOngoing = true;
		needsRender = true;
	}
	else if (window.input().isReleased(ggl::Key::A))
	{
		inputOngoing ^= false;
		needsRender = true;
	}

	if (window.input().isHeld(ggl::Key::D))
	{
		centerOffset.x -= keyboardOffset;
		needsRender = true;
		inputOngoing = true;
	}
	else if (window.input().isReleased(ggl::Key::D))
	{
		inputOngoing ^= false;
		needsRender = true;
	}

	// Mouse Input //

	if (window.input().mouseDragged(ggl::MouseButton::LEFT) && 
		hoveredVector == -1)
	{
		const glm::dvec2 cursorPosOffset = 
			window.input().getCursorMovementOffset();
		
		centerOffset.x += cursorPosOffset.x;
		centerOffset.y -= cursorPosOffset.y;

		inputOngoing = true;
		needsRender = true;
	}
	else if (window.input().isReleased(ggl::MouseButton::LEFT))
	{
		inputOngoing ^= false;
		needsRender = true;
	}
	
	gridInputOngoing = inputOngoing;
}

void VecyMain::handleVectorActions(
	const ggl::Window& window, double dt, const glm::dvec2& transformedCursorPos)
{
	bool inputOngoing = false;

	// Vector Placement
	if (window.input().isHeld(ggl::Key::CONTROL) &&
		window.input().isPressed(ggl::MouseButton::LEFT))
	{
		vectors.addVector(transformedCursorPos);
		inputOngoing = true;
		needsRender = true;
	}
	else if (
		window.input().isReleased(ggl::Key::CONTROL) ||
		window.input().isReleased(ggl::MouseButton::LEFT))
	{
		inputOngoing ^= false;
		needsRender = true;
	}

	//
	if (window.input().isHeld(ggl::Key::SHIFT))
	{
		vectors.showBasisVectors();
		inputOngoing = true;
		needsRender = true;
	}
	else if (window.input().isReleased(ggl::Key::SHIFT))
	{
		vectors.hideBasisVectors(grid.getUnitDistance());
		inputOngoing ^= false;
		needsRender = true;
	}

	if (hoveredVector != -1)
	{
		// Vector Movement
		if (window.input().isHeld(ggl::MouseButton::LEFT))
		{
			vectors.moveVector(hoveredVector, transformedCursorPos);
			noVectorSelection = false;
			inputOngoing = true;
			needsRender = true;

			if (window.input().isHeld(ggl::Key::SHIFT))
				vectors.updateBasisVectorTransform(grid.getUnitDistance());
		}
		else if (window.input().isReleased(ggl::MouseButton::LEFT))
		{
			noVectorSelection = true;
			inputOngoing ^= false;
			needsRender = true;
		}

		// Vector Removal
		if (window.input().isHeld(ggl::Key::CONTROL) &&
			window.input().isPressed(ggl::MouseButton::RIGHT))
		{
			vectors.removeVector(hoveredVector);
			inputOngoing = true;
			needsRender = true;
		}
		else if (window.input().isReleased(ggl::Key::CONTROL) ||
			window.input().isReleased(ggl::MouseButton::RIGHT))
		{
			inputOngoing ^= false;
			needsRender = true;
		}
	}

	vectorInputOngoing = inputOngoing;
}

// Game Loop Methods //

void VecyMain::processInput(const ggl::Window& window, double dt)
{
	// Transform the cursor coordinates to world coordinates.
	const glm::dvec2 transformedCursorPos(
		 2.0 * window.input().getCursorPosition().x - window.width() - centerOffset.x,
		-2.0 * window.input().getCursorPosition().y + window.height() - centerOffset.y);

	if (noVectorSelection)
	{
		hoveredVector =
			vectors.checkForSelections(transformedCursorPos, grid.getUnitDistance());
	}

	if (!vectorInputOngoing)
		handleGridNavigation(window, dt);

	if (!gridInputOngoing)
		handleVectorActions(window, dt, transformedCursorPos);
}
	
void VecyMain::render(const ggl::Window& window)
{
	if (needsRender)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		grid.render(window.width(), window.height(), centerOffset, projection);
		vectors.render(centerOffset, grid.getUnitDistance());

		needsRender = false;
		window.swapBuffers();
	}
}