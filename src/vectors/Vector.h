#ifndef VECTOR_H
#define VECTOR_H

#include <glm/glm.hpp>

static const glm::vec4 DEFAULT_COLOR(
	244.0 / 255.0, 244.0 / 255.0, 37.0 / 255.0, 1.0);

class Vector
{
private:
	glm::dmat2 getRotationTransform(const glm::dvec2& coords) const;

public:
	glm::dvec2 coords;
	glm::vec4 renderColor;

	double length;
	glm::dmat2 rotationTransform;
	glm::dmat2 rotationTransformInverse;

	Vector() = delete;
	Vector(const glm::dvec2& coords, glm::vec4 renderColor = DEFAULT_COLOR);

	void set(const glm::dvec2& newCoords);
};

#endif