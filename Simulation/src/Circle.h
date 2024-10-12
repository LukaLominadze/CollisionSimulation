#pragma once

#include <GLRenderer.h>

#include <random>

class Circle {
public:
	Circle(std::random_device& device, std::uniform_real_distribution<float>& dist);

	void OnUpdate(float timestep);

	void Collide(Circle& other);

	inline const glm::vec3 GetScale() const { return m_scale; }
	inline const ImVec4 GetColor() const { return m_color; }
	inline const float GetRadius() const { return m_radius; }
	inline const float GetMass() const { return m_mass; }

	glm::vec2 m_Velocity;
	glm::vec3 m_Position;
private:
	glm::vec3 m_scale;
	ImVec4 m_color;

	float m_radius;
	float m_mass;
};