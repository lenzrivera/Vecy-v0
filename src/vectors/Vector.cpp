#include "Vector.h"

Vector::Vector(const glm::dvec2& coords, glm::vec4 renderColor) :
	coords(coords), renderColor(renderColor),

	length(glm::length(coords)),
	rotationTransform(getRotationTransform(coords)),
	rotationTransformInverse(glm::transpose(rotationTransform))
{
}

glm::dmat2 Vector::getRotationTransform(const glm::dvec2& coords) const
{
	glm::dvec2 normCoords = glm::normalize(coords);
	glm::dvec2 perpendicular =
		glm::cross(glm::dvec3(normCoords, 0.0), glm::dvec3(0.0, 0.0, -1.0));
	return glm::dmat2(normCoords, perpendicular);
}

void Vector::set(const glm::dvec2& newCoords)
{
	coords = newCoords;
	length = glm::length(newCoords);
	rotationTransform = getRotationTransform(newCoords);
	rotationTransformInverse = glm::transpose(rotationTransform);
}