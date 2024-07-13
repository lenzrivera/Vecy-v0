#include "GridLineRenderer.h"

#include <cassert>

GridLineRenderer::GridLineRenderer(
	unsigned int initialLineCount, const glm::mat4& projection
)
	: currLineIndex(0), linesBuffer(initialLineCount),
	  lineVao(0), linesVbo(0), 
	  lineShaders(ggl::ShaderProgram::fromFiles(
		  "res/shaders/lineShaders.vert", "res/shaders/lineShaders.frag"))
{
	glGenVertexArrays(1, &lineVao);
	glBindVertexArray(lineVao);
	
	glGenBuffers(1, &linesVbo);
	glBindBuffer(GL_ARRAY_BUFFER, linesVbo);
	glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, sizeof(glm::dvec2), 0);
	glEnableVertexAttribArray(0);
	
	glBufferData(GL_ARRAY_BUFFER, 
		initialLineCount * sizeof(LineVertices), nullptr, GL_DYNAMIC_DRAW);
		
	lineShaders->use();
	lineShaders->setUniform("u_projection", projection);
}

GridLineRenderer::~GridLineRenderer()
{
	glDeleteVertexArrays(1, &lineVao);
	glDeleteBuffers(1, &linesVbo);
}

void GridLineRenderer::adjustLineStroke(
	unsigned int index, double dWidth, double dHeight)
{
	assert(index < linesBuffer.size());
	linesBuffer[index].adjustStroke(dWidth, dHeight);
}
	
void GridLineRenderer::bufferLine(
	const glm::dvec2& center, double width, double height)
{
	assert(currLineIndex < linesBuffer.size());
	linesBuffer[currLineIndex].set(center, width, height);
	currLineIndex += 1;
}
	
void GridLineRenderer::render()
{
	glBindBuffer(GL_ARRAY_BUFFER, linesVbo);
	glBufferSubData(GL_ARRAY_BUFFER,
		0, linesBuffer.size() * sizeof(LineVertices), linesBuffer.data());
	
	glBindVertexArray(lineVao);
	lineShaders->use();
	glDrawArrays(GL_TRIANGLES, 0, linesBuffer.size() * 6);	

	currLineIndex = 0;
}