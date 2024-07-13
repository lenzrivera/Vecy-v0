#ifndef GRID_H
#define GRID_H

#include "GridLabelRenderer.h"
#include "GridLineRenderer.h"

// So I messed up - maybe I should have hardcoded the unitDistance, and
// parametrized the number of rendered horizontal and vertical units in a 
// dedicated method instead of hardcoding them initially. Those would have
// allowed for 1.) easier dynamic grid rendering when window resizing, and 
// 2.) simpler, more fundamental grid code. Welp :'D

class Grid
{
private:
	// Grid State //

	/**
	 * @brief The number of RENDERED horizontal lines starting from x = 0 to
	 * any POSITIVE (going right) whole number. This number is always greater
	 * than 2 as x = 0 and a line at the far edge of the screen (practically
	 * invisible, but required for correct-looking grid scrolling) should
	 * always be present/rendered.
	 */
	int baseHorizontalUnits;

	/**
	 * @brief The total number of RENDERED horizontal lines.
	 */
	int totalHorizonalUnits;

	/**
	 * @brief The constant distance between two lines, whether horizontal or
	 * vertical.
	 */
	double unitDistance;

	/**
	 * @brief The number of RENDERED vertical lines starting from x = 0 to
	 * any POSITIVE (going right) whole number. This number is always greater
	 * than 2 as y = 0 and a line at the far edge of the screen (practically
	 * invisible, but required for correct-looking grid scrolling) should
	 * always be present/rendered.
	 */
	int baseVerticalUnits;

	// Render Stuffs //

	GridLabelRenderer gridLabels;
	GridLineRenderer gridLines;

	void prepareXAxisRender(
		int width, int height, 
		const glm::dvec2& centerOffset, const glm::dmat4& projection);
	void prepareYAxisRender(
		int width, int height, 
		const glm::dvec2& centerOffset, const glm::dmat4& projection);

public:
	Grid() = delete;
	Grid(int width, int height, const glm::dmat4& projection);

	double getUnitDistance() const;

	void render(
		int width, int height, 
		const glm::dvec2& centerOffset, const glm::dmat4& projection);
};

#endif