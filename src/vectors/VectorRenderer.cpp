#include "VectorRenderer.h"

#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>

#include "VectorVertices.h"

VectorRenderer::VectorRenderer(const glm::dmat4& projection)
	: vectorVao(0), vectorVbo(0), 
	  vectorShaders(ggl::ShaderProgram::fromFiles(
		  "res/shaders/vectorShaders.vert", "res/shaders/vectorShaders.frag"))
{
	glGenVertexArrays(1, &vectorVao);
	glBindVertexArray(vectorVao);

	glGenBuffers(1, &vectorVbo);
	glBindBuffer(GL_ARRAY_BUFFER, vectorVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VectorVertices), nullptr, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, sizeof(glm::dvec2), 0);
	glEnableVertexAttribArray(0);

	vectorShaders->use();
	vectorShaders->setUniform("u_projection", projection);
}

VectorRenderer::~VectorRenderer()
{
	glDeleteVertexArrays(1, &vectorVao);
	glDeleteBuffers(1, &vectorVbo);
}

void VectorRenderer::render(
	const Vector& vector, double unitDistance, const glm::vec2& renderOffset) const
{
	VectorVertices vertices(vector, unitDistance);
	glBindBuffer(GL_ARRAY_BUFFER, vectorVbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices.vertices);

	glBindVertexArray(vectorVao);
	vectorShaders->use();
	vectorShaders->setUniform("u_color", vector.renderColor);
	vectorShaders->setUniform("u_model", vector.rotationTransform);
	vectorShaders->setUniform("u_renderOffset", renderOffset);

	glDrawArrays(GL_TRIANGLES, 0, 9);
}