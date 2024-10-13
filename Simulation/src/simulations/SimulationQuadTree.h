#pragma once

#include "Simulation.h"
#include "QuadTree.h"

class SimulationQuadTree : public Simulation
{
public:
	SimulationQuadTree();

	void OnFixedUpdate() override;
	void OnGizmoRender(Renderer& renderer) override;
	void OnImGuiRender() override;
private:
	QuadTree m_tree;
	std::vector<Boundary> m_boundaries;

	int m_capacity;
};

