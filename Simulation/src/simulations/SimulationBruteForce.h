#pragma once

#include "Simulation.h"

class SimulationBruteForce : public Simulation
{
public:
	void OnFixedUpdate() override;
	void OnImGuiRender() override;
};

