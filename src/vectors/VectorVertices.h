#ifndef VECTOR_VERTICES_H
#define VECTOR_VERTICES_H

#include <glm/glm.hpp>

#include "Vector.h"
#include "VectorBounds.h"

using namespace VectorBounds;

struct VectorVertices
{
	glm::dvec2 vertices[9];

	VectorVertices(const Vector& vector, double unitDistance) : 
		VectorVertices(
			getHeadHeight(unitDistance), 
			getTailHeight(unitDistance),
			getTailLength(vector, unitDistance),
			vector.length)
	{
	}

	VectorVertices(
		double headHeight, double tailHeight, double tailLength, double vectorLength
	) : 
		VectorVertices(
			VectorHead(headHeight, tailLength, vectorLength),
			VectorTail(tailHeight, tailLength))
	{
	}

	VectorVertices(VectorHead head, VectorTail tail) : 
		vertices{
			tail.upperLeft, tail.lowerLeft, tail.upperRight, 
			tail.upperRight, tail.lowerLeft, tail.lowerRight,
	
			head.upper, head.lower, head.tip}
	{
	}
};

#endif