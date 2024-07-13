#ifndef GRID_TEXT_RENDERER_H
#define GRID_TEXT_RENDERER_H

#include <glm/glm.hpp>

#include <ggl.h>
#include <gly.h>

class GridLabelRenderer
{
private:
	gly::Text textRenderer;
	gly::FontFace labelFont;

	double maxFontWidth, maxFontHeight;
	glm::dvec2 labelMargin;
	
public:
	GridLabelRenderer() = delete;
	GridLabelRenderer(unsigned int fontPxHeight, glm::dvec2 labelMargin);
	
	void renderXAxisLabel(
		int label, const glm::dvec2& center, const glm::dmat4& projection, 
		int gridHeight);
	void renderYAxisLabel(
		int label, const glm::dvec2& center, const glm::dmat4& projection,
		int gridWidth);
};

#endif