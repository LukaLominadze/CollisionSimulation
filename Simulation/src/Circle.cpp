#include "Circle.h"

#include <algorithm>

#define PI 3.14159265359

Circle::Circle(std::random_device& device, std::uniform_real_distribution<float>& dist)
{
	float scale = std::clamp(abs(dist(device)), 0.1f, 0.6f);

	m_Position = glm::vec3(dist(device), dist(device), dist(device));
	m_scale = glm::vec3(scale);
	m_color = ImVec4(abs(dist(device)), abs(dist(device)), abs(dist(device)), 1.0f);

	m_radius = scale * 0.1f;
	m_mass = m_radius;

	m_Velocity = glm::vec2(dist(device) * 0.4f, dist(device) * 0.4f);
}

void Circle::OnUpdate(float timestep)
{
	float radius = m_scale.x * 0.1f;
	if (m_Position.x - radius < -1.0f || m_Position.x + radius > 1.0f) {
		m_Position.x = (abs(m_Position.x) / m_Position.x) * (1.0f - radius);
		m_Velocity.x = -m_Velocity.x;
	}
	else if (m_Position.y - radius < -1.0f || m_Position.y + radius > 1.0f) {
		m_Position.y = (abs(m_Position.y) / m_Position.y) * (1.0f - radius);
		m_Velocity.y = -m_Velocity.y;
	}

	m_Position = glm::vec3(m_Position.x + m_Velocity.x * timestep, m_Position.y + m_Velocity.y * timestep, m_Position.z);
}

void Circle::Collide(Circle& other)
{
	glm::vec2 delta(other.m_Position.x - m_Position.x, other.m_Position.y - m_Position.y);
	float distance = glm::length(delta);
	float radiusSum = m_radius + other.GetRadius();
	if (distance > radiusSum) {
		return;
	}

	float offset = abs(distance - (m_radius + other.GetRadius()));
	glm::vec2 normal(glm::normalize(delta));

	m_Position = glm::vec3(m_Position.x - normal.x * offset / 2.0f,
						   m_Position.y - normal.y * offset / 2.0f, m_Position.z);
	other.m_Position = glm::vec3(other.m_Position.x + normal.x * offset / 2.0f,
								 other.m_Position.y + normal.y * offset / 2.0f, other.m_Position.z);

	float angleA = atan2(m_Velocity.y, m_Velocity.x);
	float angleB = atan2(other.m_Velocity.y, other.m_Velocity.x);
	float angleContact = atan2(other.m_Position.y - m_Position.y, other.m_Position.x - m_Position.x);

	float massB = other.GetMass();
	float massSum = m_mass + massB;
	float massSub = m_mass - massB;

	float velA = glm::length(m_Velocity);
	float velB = glm::length(other.m_Velocity);

	float velAx = ((velA * cosf(angleA - angleContact) * massSub +
		2 * massB * velB * cos(angleB - angleContact)) / massSum) * cos(angleContact) +
		velA * sin(angleA - angleContact) * cos(angleContact + PI / 2.0f);
	float velAy = ((velA * cosf(angleA - angleContact) * massSub +
		2 * massB * velB * cos(angleB - angleContact)) / massSum) * sin(angleContact) +
		velA * sin(angleA - angleContact) * sin(angleContact + PI / 2.0f);

	float velBx = ((velB * cosf(angleB - angleContact) * -massSub +
		2 * m_mass * velA * cos(angleA - angleContact)) / massSum) * cos(angleContact) +
		velB * sin(angleB - angleContact) * cos(angleContact + PI / 2.0f);
	float velBy = ((velB * cosf(angleB - angleContact) * -massSub +
		2 * m_mass * velA * cos(angleA - angleContact)) / massSum) * sin(angleContact) +
		velB * sin(angleB - angleContact) * sin(angleContact + PI / 2.0f);

	m_Velocity = glm::vec2(velAx, velAy);
	other.m_Velocity = glm::vec2(velBx, velBy);
}
