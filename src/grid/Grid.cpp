#include "Grid.h"

#include <cmath>

#include <glm/ext.hpp>

static const double GRID_LINE_STROKE = 2.5;
static const unsigned int INITIAL_VISIBLE_UNITS = 4;
static const unsigned int LABELS_FONT_PX_HEIGHT = 50;
static const glm::dvec2 LABELS_MARGIN(15.0, 18.0);

Grid::Grid(int width, int height, const glm::dmat4& projection) : 
	baseHorizontalUnits(INITIAL_VISIBLE_UNITS + 2),
	totalHorizonalUnits(2 * baseHorizontalUnits - 1),
	unitDistance(width / (baseHorizontalUnits - 1)),
	baseVerticalUnits(static_cast<unsigned int>(
		std::floor(height / unitDistance) + 2)),

	gridLabels(LABELS_FONT_PX_HEIGHT, LABELS_MARGIN),
	gridLines( 
		// Total Horizontal Units + Total Vertical Units
		totalHorizonalUnits + 2 * (baseVerticalUnits - 1) + 2,
		projection)
{
}

void Grid::prepareXAxisRender(
	int width, int height,
	const glm::dvec2& centerOffset, const glm::dmat4& projection)
{
	int xLabelOffset = static_cast<int>(-std::trunc(centerOffset.x / unitDistance));
	// The grid can repeat itself when offset a multiple of unitDistance.
	double xRenderOffset = std::fmod(centerOffset.x, unitDistance);

	// Buffer/render the line/label center to the grid first to not repeat it
	// later (not necessarily the origin!).
	gridLines.bufferLine({ xRenderOffset, 0.0 }, GRID_LINE_STROKE, height);
	gridLabels.renderXAxisLabel(
		xLabelOffset, { xRenderOffset, centerOffset.y }, projection, height);

	// Then, buffer/render the remaining lines/labels by symmetry (by virtue of
	// our projection matrix!).
	for (int i = 1; i < baseHorizontalUnits; i++)
	{
		double baseX = unitDistance * i;
		double posBaseX =  baseX + xRenderOffset;
		double negBaseX = -baseX + xRenderOffset;

		gridLines.bufferLine({ posBaseX, 0.0 }, GRID_LINE_STROKE, height);
		gridLines.bufferLine({ negBaseX, 0.0 }, GRID_LINE_STROKE, height);

		gridLabels.renderXAxisLabel( i + xLabelOffset, 
			{ posBaseX, centerOffset.y }, projection, height);
		gridLabels.renderXAxisLabel(-i + xLabelOffset, 
			{ negBaseX, centerOffset.y }, projection, height);
	}

	// Thicken the origin line's stroke if it is visible.
	int baseLabelOffset = std::abs(xLabelOffset);
	if (baseLabelOffset < baseHorizontalUnits)
	{
		// Due to how the lines are buffered (for efficiency), some weirdness
		// has to be done to determine where the origin line is. The code below
		// is equivalent to:
		//
		//    // Base case where the origin line is at x = 0.
		//    int labelIndex = 0;
		//    
		//    // Origin line along negative x-axis; skip index by two.
		//    if (xLabelOffset > 0) 
		//        labelIndex = 2 * baseLabelOffset;
		//
		//    // Origin line along positive x-axis; skip index by odd numbers.
		//    // (Sort of; the formula below is because baseLabelOffset == 1 
		//    // should correspond to 1, not 3).
		//    else if (xLabelOffset < 0) 
		//	      labelIndex = 2 * (baseLabelOffset - 1) + 1;
		//
		int labelIndex = 2 * baseLabelOffset;
		if (xLabelOffset < 0)
			labelIndex -= 1;

		gridLines.adjustLineStroke(labelIndex, 1.5 * GRID_LINE_STROKE, 0.0);
	}
}

void Grid::prepareYAxisRender(
	int width, int height, 
	const glm::dvec2& centerOffset, const glm::dmat4& projection)
{
	// This code works on the same principles as prepareXAxisRender(), though
	// its differences wont allow it to be easily refactored.

	int yLabelOffset = static_cast<int>(-std::trunc(centerOffset.y / unitDistance));
	double yRenderOffset = std::fmod(centerOffset.y, unitDistance);

	gridLines.bufferLine({ 0.0, yRenderOffset }, width, GRID_LINE_STROKE);
	gridLabels.renderYAxisLabel(
		yLabelOffset, { centerOffset.x, yRenderOffset }, projection, width);

	for (int i = 1; i < baseVerticalUnits; i++)
	{
		double baseY = unitDistance * i;
		double posBaseY =  baseY + yRenderOffset;
		double negBaseY = -baseY + yRenderOffset;

		gridLines.bufferLine({ 0.0, posBaseY }, width, GRID_LINE_STROKE);
		gridLines.bufferLine({ 0.0, negBaseY }, width, GRID_LINE_STROKE);

		gridLabels.renderYAxisLabel( i + yLabelOffset,
			{ centerOffset.x, posBaseY }, projection, width);
		gridLabels.renderYAxisLabel(-i + yLabelOffset,
			{ centerOffset.x, negBaseY }, projection, width);
	}

	int baseLabelOffset = std::abs(yLabelOffset);
	if (baseLabelOffset < baseVerticalUnits)
	{
		// The y-axis lines are buffered after the x-axis lines.
		int labelIndex = totalHorizonalUnits + 2 * baseLabelOffset;
		if (yLabelOffset < 0)
			labelIndex -= 1;
		
		gridLines.adjustLineStroke(labelIndex, 0.0, 1.5 * GRID_LINE_STROKE);
	}
}

double Grid::getUnitDistance() const
{
	return unitDistance;
}

void Grid::render(
	int width, int height, 
	const glm::dvec2& centerOffset, const glm::dmat4& projection)
{
	prepareXAxisRender(width, height, centerOffset, projection);
	prepareYAxisRender(width, height, centerOffset, projection);

	gridLines.render();
}