#pragma once

#include "Circle.h"

struct Boundary {
	Boundary() = default;
	Boundary(const Boundary& other);
	Boundary(float x, float y, float width, float height);

	bool ContainsCenter(const Boundary& other);
	bool IntersectsCircle(const Circle& circle);
	bool Intersects(const Boundary& other);

	float x1, y1, x2, y2;
};