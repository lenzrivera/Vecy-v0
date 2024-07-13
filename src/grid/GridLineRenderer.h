#ifndef GRID_LINE_RENDERER_H
#define GRID_LINE_RENDERER_H

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "ggl.h"

#include "LineVertices.h"

class GridLineRenderer
{
private:
	unsigned int currLineIndex;
	std::vector<LineVertices> linesBuffer;

	GLuint lineVao;
	GLuint linesVbo;
	ggl::ShaderProgram::Pointer lineShaders;
	
public:
	GridLineRenderer(unsigned int initialLineCount, const glm::mat4& projection);
	~GridLineRenderer();
	
	void adjustLineStroke(unsigned int index, double dWidth, double dHeight);
	void bufferLine(const glm::dvec2& center, double width, double height);
	
	void render();
};

#endif