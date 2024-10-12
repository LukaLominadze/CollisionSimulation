#pragma once

#include "Simulation.h"

class SimulationBruteForce : public Simulation
{
public:
	void OnUpdate(float timestep) override;
	void OnImGuiRender() override;
};

