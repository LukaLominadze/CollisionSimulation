#include "Boundary.h"

Boundary::Boundary(const Boundary& other)
{
	x1 = other.x1;
	x2 = other.x2;
	y1 = other.y1;
	y2 = other.y2;
	width = other.width;
	height = other.height;
}

Boundary::Boundary(float x, float y, float width, float height) {
	x1 = x - width / 2.0f;
	y1 = y - height / 2.0f;
	x2 = x + width / 2.0f;
	y2 = y + height / 2.0f;
	this->width = width;
	this->height = height;
}

bool Boundary::ContainsCenter(const Boundary& circle) {
	glm::vec2 position(circle.x1 + circle.width / 2.0f, circle.y1 + circle.height / 2.0f);
	return (position.x >= x1 && position.x <= x2 && position.y <= y2 && position.y >= y1);
}

bool Boundary::IntersectsCircle(const Circle& circle)
{
	glm::vec2 position = circle.m_Position;
	float radius = circle.GetRadius();
	return (position.x - radius < x2 && position.x + radius > x1 && position.y - radius < y2 && position.y + radius > y1);
}

bool Boundary::Intersects(const Boundary& other) {
	return (other.x1 < x2 && other.x2 > x1 && other.y1 < y2 && other.y2 > y1);
}