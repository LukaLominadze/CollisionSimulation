#pragma once

#include <GLRenderer.h>

#include "simulations/Simulation.h"

class SimulationLayer : public Layer
{
public:
	void OnAttach() override;
	void OnEvent(Event& event) override;
	void OnUpdate(float timestep) override;
	void OnRender(Renderer& renderer) override;
	void OnImGuiRender() override;

	template<typename T>
	void RegisterSimulation(const std::string& name) {
		LOG("Registering simulation... " << name)
			m_simulations.push_back(std::make_pair(name, []() { return new T(); }));
	}
private:
	Simulation* p_currentSimulation = nullptr;
	std::vector<std::pair<std::string, std::function<Simulation* ()>>> m_simulations;
};