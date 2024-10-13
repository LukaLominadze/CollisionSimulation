#pragma once

#include "Simulation.h"

#include <unordered_map>

class SimulationSpacePartition : public Simulation {
public:
	SimulationSpacePartition();

	void OnFixedUpdate() override;
	void OnGizmoRender(Renderer& renderer) override;
	void OnImGuiRender() override;
private:
	int GetGridIndex(float x, float y);
	int GetGridIndex(int x, int y);
private:
	int m_gridSize = 2;

	std::unordered_map<int, std::vector<int>> m_grid;
};