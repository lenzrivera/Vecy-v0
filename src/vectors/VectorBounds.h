#ifndef VECTOR_BOUNDS_H
#define VECTOR_BOUNDS_H

#include <glm/glm.hpp>

#include "Vector.h"

namespace VectorBounds
{
	// Coordinate/Length Retrieval //

	inline double getHeadHeight(double unitDistance)
	{
		return 0.09 * unitDistance;
	}

	inline double getTailLength(const Vector& vector, double unitDistance)
	{
		return vector.length - 0.15 * unitDistance;
	}

	inline double getTailHeight(double unitDistance)
	{
		return 0.02 * unitDistance;
	}

	// Bounds Structs //

	struct VectorHead
	{
		glm::dvec2 upper;
		glm::dvec2 lower;
		glm::dvec2 tip;

		VectorHead(const Vector& vector, double unitDistance) :
			VectorHead(
				getHeadHeight(unitDistance), 
				getTailLength(vector, unitDistance), 
				vector.length)
		{
		}

		VectorHead(double headHeight, double tailLength, double vectorLength) : 
			upper(tailLength, headHeight), 
			lower(tailLength, -headHeight), 
			tip(vectorLength, 0.0)
		{

		}
	};

	struct VectorTail
	{
		glm::dvec2 upperLeft;
		glm::dvec2 lowerLeft;
		glm::dvec2 upperRight;
		glm::dvec2 lowerRight;

		VectorTail(const Vector& vector, double unitDistance) : 
			VectorTail(
				getTailHeight(unitDistance), getTailLength(vector, unitDistance))
		{
		}

		VectorTail(double tailHeight, double tailLength) :
			upperLeft(0.0, tailHeight), lowerLeft(0.0, -tailHeight),
			upperRight(tailLength, tailHeight), lowerRight(tailLength, -tailHeight)
		{
		}
	};

	struct VectorSelectionBounds
	{
		glm::dvec2 upperLeft;
		glm::dvec2 lowerLeft;
		glm::dvec2 upperRight;
		glm::dvec2 lowerRight;

		VectorSelectionBounds(const Vector& vector, double unitDistance) :
			VectorSelectionBounds(
				getHeadHeight(unitDistance), 
				getTailLength(vector, unitDistance), 
				vector.length)
		{
		}

		VectorSelectionBounds(
			double headHeight, double tailLength, double vectorLength
		) :
			upperLeft(tailLength, headHeight), 
			lowerLeft(tailLength, -headHeight),
			upperRight(vectorLength, headHeight), 
			lowerRight(vectorLength, -headHeight)
		{
		}

		inline bool selected(const glm::dvec2& transformedCursorPos)
		{
			return upperLeft.x <= transformedCursorPos.x &&
				lowerRight.x >= transformedCursorPos.x &&
				upperLeft.y >= transformedCursorPos.y &&
				lowerRight.y <= transformedCursorPos.y;
		}

	};

}

#endif