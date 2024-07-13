#ifndef LINE_VERTICES_H
#define LINE_VERTICES_H

#include <glm/glm.hpp>

struct LineVertices
{
	glm::dvec2 vertices[6];

	LineVertices()
		: vertices()
	{
	}

	inline void adjustStroke(double dWidth, double dHeight)
	{
		// Top-left
		vertices[0].x -= dWidth;
		vertices[0].y += dHeight;

		// Bottom-left
		vertices[1].x = vertices[0].x;
		vertices[1].y -= dHeight;

		// Top-right
		vertices[2].x += dWidth;
		vertices[2].y = vertices[0].y;

		vertices[3] = vertices[2];
		vertices[4] = vertices[1];

		// Bottom-right
		vertices[5].x = vertices[2].x;
		vertices[5].y = vertices[1].y;
	}

	inline void set(const glm::dvec2& center, double width, double height)
	{
		// Top-left
		vertices[0].x = center.x - width;
		vertices[0].y = center.y + height;

		// Bottom-left
		vertices[1].x = vertices[0].x;
		vertices[1].y = center.y - height;

		// Top-right
		vertices[2].x = center.x + width;
		vertices[2].y = vertices[0].y;

		vertices[3] = vertices[2];
		vertices[4] = vertices[1];

		// Bottom-right
		vertices[5].x = vertices[2].x;
		vertices[5].y = vertices[1].y;
	}
};

#endif