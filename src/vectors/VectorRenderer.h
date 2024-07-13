#ifndef VECTOR_RENDERER_H
#define VECTOR_RENDERER_H

#include <GL/glew.h>

#include "ggl.h"

#include "Vector.h"

class VectorRenderer
{
private:
	GLuint vectorVao;
	GLuint vectorVbo;
	ggl::ShaderProgram::Pointer vectorShaders;

public:
	VectorRenderer() = delete;
	VectorRenderer(const glm::dmat4& projection);
	~VectorRenderer();

	void render(
		const Vector& vector, 
		double unitDistance,
		const glm::vec2& renderOffset) const;
};

#endif