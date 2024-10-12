#include "Circle.h"

#define PI 3.14159265359

Circle::Circle(std::random_device& device, std::uniform_real_distribution<float>& dist)
{
	float scale = abs(dist(device));

	m_Position = glm::vec3(dist(device), dist(device), dist(device));
	m_scale = glm::vec3(scale);
	m_color = ImVec4(abs(dist(device)), abs(dist(device)), abs(dist(device)), 1.0f);

	m_radius = scale * 0.1f;
	LOG(m_radius);
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
	float deltaX = other.m_Position.x - m_Position.x;
	float deltaY = other.m_Position.y - m_Position.y;
	float distance = sqrt(deltaX * deltaX + deltaY * deltaY);
	if (distance > m_radius + other.GetRadius()) {
		return;
	}

	float offset = abs(distance - (m_radius + other.GetRadius()));
	float normalX = deltaX / distance;
	float normalY = deltaY / distance;

	m_Position = glm::vec3(m_Position.x - normalX * offset / 2.0f,
						   m_Position.y - normalY * offset / 2.0f, m_Position.z);
	other.m_Position = glm::vec3(other.m_Position.x + normalX * offset / 2.0f,
								 other.m_Position.y + normalY * offset / 2.0f, other.m_Position.z);

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

	glm::vec2 velocityA(velAx, velAy);
	glm::vec2 velocityB(velBx, velBy);

	m_Velocity = velocityA;
	other.m_Velocity = velocityB;
}
