#include "VectorManager.h"

#include "VectorBounds.h"

using namespace VectorBounds;

static const unsigned int BASIS_VECTORS_START = 0;
static const unsigned int OTHER_VECTORS_START = 2;

static const glm::vec4 I_HAT_COLOR(98.0 / 255.0, 199.0 / 255.0, 96.0 / 255.0, 1.0);
static const glm::vec4 J_HAT_COLOR(223.0 / 255.0, 83.0 / 255.0, 83.0 / 255.0, 1.0);

VectorManager::VectorManager(double unitDistance, const glm::mat4& projection) : 
	indexOffset(OTHER_VECTORS_START),
	vectors({ 
		Vector({ unitDistance, 0.0 }, I_HAT_COLOR), // i-hat
		Vector({ 0.0, unitDistance }, J_HAT_COLOR)  // j-hat
	}), 
		
	basisTransform(1.0f), vectorRenderer(projection)
{
}

// Vector Manipulation //

void VectorManager::addVector(const glm::dvec2& vecCoords)
{
	vectors.push_back(Vector(vecCoords));
}

void VectorManager::moveVector(
	unsigned int index, const glm::dvec2& destCoords)
{
	assert(index < vectors.size());
	vectors[index].set(destCoords);
}

void VectorManager::removeVector(unsigned int index)
{
	assert(index < vectors.size());
	vectors.erase(vectors.begin() + index);
}

// Vector State //

int VectorManager::checkForSelections(
	const glm::dvec2& currCursorPos, double unitDistance) const
{
	for (auto v = vectors.begin() + indexOffset; v < vectors.end(); v++)
	{
		VectorSelectionBounds selectionBounds(*v, unitDistance);
		glm::dvec2 basePos = v->rotationTransformInverse * currCursorPos;

		if (selectionBounds.selected(basePos))
			return v - vectors.begin();
	}

	return -1;
}

void VectorManager::hideBasisVectors(double unitDistance)
{
	// Fully update the position...
	/* Maybe the temporary resultant basis vector transformations should be stored
	   in the vectors themselves, and then once complete just reset their coordinates,
	   instead of recomputing them like this. */
	for (auto v = vectors.begin() + OTHER_VECTORS_START; v < vectors.end(); v++)
		v->set(basisTransform * v->coords);

	// Reset basis vectors' positions.
	basisTransform[0] = { 1.0, 0.0 };
	basisTransform[1] = { 0.0, 1.0 };
	vectors[BASIS_VECTORS_START].set({ unitDistance, 0.0 });
	vectors[BASIS_VECTORS_START + 1].set({ 0.0, unitDistance });
	
	indexOffset = OTHER_VECTORS_START;
}

void VectorManager::showBasisVectors()
{
	indexOffset = BASIS_VECTORS_START;
}

// Main Loop Methods //

void VectorManager::updateBasisVectorTransform(double unitDistance)
{
	basisTransform[BASIS_VECTORS_START] = vectors[0].coords / unitDistance;
	basisTransform[BASIS_VECTORS_START + 1] = vectors[1].coords / unitDistance;
}

void VectorManager::render(const glm::dvec2& renderOffset, double unitDistance)
{
	for (auto bv = vectors.begin() + indexOffset;
		      bv < vectors.begin() + OTHER_VECTORS_START; bv++)
	{
		vectorRenderer.render(*bv, unitDistance, renderOffset);
	}

	for (auto v = vectors.begin() + OTHER_VECTORS_START; v < vectors.end(); v++)
	{
		Vector vv(basisTransform * v->coords);
		vectorRenderer.render(vv, unitDistance, renderOffset);
	}
}