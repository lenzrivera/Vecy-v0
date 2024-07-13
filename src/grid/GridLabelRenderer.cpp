#include "GridLabelRenderer.h"

#include <string>

// This class would very much benefit from having its own text rendering 
// engine, because:
// 
// 1.) gly can be garbage.
// 2.) Only glyphs for '0' to '9' need to be loaded.
// 3.) Computations for maximum glyph height and phrase width should be
//	   supported to properly peform label position clamping.
// 4.) Projection should be set only once during initialization to minimize
//     gpu communication.

GridLabelRenderer::GridLabelRenderer(
	unsigned int fontPxHeight, glm::dvec2 labelMargin
)
	: textRenderer(), 
	  labelFont(textRenderer.loadFont("res/fonts/cambria.ttc", 0, fontPxHeight)), 
	
	  // Only an estimate...
	  maxFontWidth(
		  static_cast<double>(labelFont.getCharData('1').size.x) +
		  static_cast<double>(labelFont.getCharData('1').bearing.x)),

	  // For this font (and probably for most), all numbers should have the same
	  // height, so this should suffice.
	  maxFontHeight(labelFont.getCharData('1').size.y),

	  labelMargin(labelMargin)
{
}

void GridLabelRenderer::renderXAxisLabel(
	int label, const glm::dvec2& center, const glm::dmat4& projection,
	int gridHeight)
{
	double labelX = center.x + labelMargin.x;

	// Labels along the x-axis can scroll freely along the x-axis, but are clamped
	// to the vertical height of the grid.
	double labelY = glm::clamp(center.y - labelMargin.y, 
		-gridHeight + maxFontHeight + labelMargin.y, gridHeight - labelMargin.y);

	textRenderer.render(
		std::to_string(label), labelFont, 1.0f, glm::vec4(1.0f),
		glm::vec4(labelX, labelY, 0.0f, 1.0f), projection);
}

void GridLabelRenderer::renderYAxisLabel(
	int label, const glm::dvec2& center, const glm::dmat4& projection, 
	int gridWidth)
{
	std::string labelStr = std::to_string(label);
	
	double labelY = center.y - labelMargin.y;

	// Labels along the y-axis can scroll freely along the y-axis, but are clamped
	// to the horizontal width of the grid.
	double clampW = labelStr.size() * maxFontWidth;
	double labelX = glm::clamp(center.x + labelMargin.x,
		-gridWidth + labelMargin.x, gridWidth - clampW - labelMargin.x);

	textRenderer.render(
		labelStr, labelFont, 1.0f, glm::vec4(1.0f),
		glm::vec4(labelX, labelY, 0.0f, 1.0f), projection);
}