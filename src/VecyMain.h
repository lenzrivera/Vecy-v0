#ifndef VECYMAIN_H
#define VECYMAIN_H

#include <glm/glm.hpp>

#include <ggl.h>

#include "grid/Grid.h"
#include "vectors/VectorManager.h"

class VecyMain
{
private:

	// Input Management //

	int hoveredVector;
	bool noVectorSelection;

	bool gridInputOngoing;
	bool vectorInputOngoing;

	// Render State //

	bool needsRender;

	glm::dvec2 centerOffset;
	glm::dmat4 projection;

	// Application Components //

	Grid grid;
	VectorManager vectors;
	
public:
	VecyMain() = delete;
	VecyMain(const ggl::Window& window);
	
	// Input Management //

	void handleGridNavigation(const ggl::Window& window, double dt);
	void handleVectorActions(
		const ggl::Window& window, double dt, const glm::dvec2& transformedCursorPos);

	// Game Loop Methods //
	
	void processInput(const ggl::Window& window, double dt);
	void render(const ggl::Window& window);
};

#endif