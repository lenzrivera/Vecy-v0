#ifndef VECTOR_MANAGER_H
#define VECTOR_MANAGER_H

#include <vector>

#include <glm/glm.hpp>

#include "Vector.h"
#include "VectorRenderer.h"

class VectorManager
{
private:
	unsigned int indexOffset;
	std::vector<Vector> vectors;

	glm::dmat2 basisTransform;
	VectorRenderer vectorRenderer;

public:
	VectorManager() = delete;
	VectorManager(double unitLength, const glm::mat4& projection);

	void addVector(const glm::dvec2& vecCoords);
	void moveVector(unsigned int index, const glm::dvec2& destCoords);
	void removeVector(unsigned int index);

	int checkForSelections(const glm::dvec2& currCursorPos, double unitDistance) const;
	void hideBasisVectors(double unitDistance);
	void showBasisVectors();

	void updateBasisVectorTransform(double unitDistance);
	void render(const glm::dvec2& renderOffset, double unitDistance);
};

#endif