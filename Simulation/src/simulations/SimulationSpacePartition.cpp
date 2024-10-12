#include "SimulationSpacePartition.h"

#include <cmath>

SimulationSpacePartition::SimulationSpacePartition()
{
	int startPos = -10;
	int endPos = 10;
	for (int x = startPos; x < endPos; x += m_gridSize) {
		for (int y = startPos; y < endPos; y += m_gridSize) {
			int index = GetGridIndex(x, y);
			m_grid[index] = std::vector<int>();
		}
	}
}

void SimulationSpacePartition::OnFixedUpdate()
{
	int startPos = -10;
	int endPos = 10;
	for (int i = 0; i < m_circles.size(); i++) {
		int index = GetGridIndex(m_circles[i].m_Position.x, m_circles[i].m_Position.y);
		m_grid[index].push_back(i);
	}
	for (int x = startPos; x < endPos; x += m_gridSize) {
		for (int y = startPos; y < endPos; y += m_gridSize) {
			int gridIndex = GetGridIndex(x, y);
			for (int dx = x - m_gridSize; dx <= x + 1 * m_gridSize; dx += m_gridSize) {
				if (dx < -10 || dx >= 10)
					continue;
				for (int dy = y - m_gridSize; dy <= y + 1 * m_gridSize; dy += m_gridSize) {
					if (dy < -10 || dy >= 10)
						continue;
					int neighbor = GetGridIndex(dx, dy);
					for (int circle : m_grid[gridIndex]) {
						for (int other : m_grid[neighbor]) {
							if (neighbor == gridIndex && circle == other)
								continue;
							m_circles[circle].Collide(m_circles[other]);
						}
					}
				}
			}
		}
	}
	for (auto it = m_grid.begin(); it != m_grid.end(); ++it) {
		it->second.clear();
	}
}

void SimulationSpacePartition::OnImGuiRender()
{
	ImGui::Begin("Stats");

	ImGui::Text("Space Partitioning Algorithm\n\nThis algorithm creates a grid \nof the existing scene");
	ImGui::Text("where every object gets \nassigned to that grid");
	ImGui::Text("based on it's position. \nThis way the objects only look through\nTheir grid and their sorrounding\ngrids. Making this algorithm\n a runtime complexity of O(nlongn)\n\n\n");

	ImGui::Text("Algorithm speed");
	ImGui::Text((std::to_string(m_ms) + " ms.").c_str());
	ImGui::Text(("FPS : " + std::to_string(1 / m_timestep)).c_str());
	ImGui::Text(("Circle Count : " + std::to_string(GetCircleCount())).c_str());

	ImGui::End();
}

int SimulationSpacePartition::GetGridIndex(float x, float y)
{
	return GetGridIndex((int)(x * 10), (int)(y * 10));
}

int SimulationSpacePartition::GetGridIndex(int x, int y)
{
	x = std::clamp(x, -10, 10);
	if (x == 10) x -= m_gridSize; 
	int clampedX = ((x + 10) / m_gridSize) * m_gridSize - 10;

	y = std::clamp(y, -10, 10);
	if (y == 10) y -= m_gridSize;
	int clampedY = ((y + 10) / m_gridSize) * m_gridSize - 10;
	return static_cast<int>(clampedX * 10 + clampedY * 100);
}
