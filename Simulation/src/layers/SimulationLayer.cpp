#include "SimulationLayer.h"

#include "simulations/SimulationBruteForce.h"

void SimulationLayer::OnAttach()
{
	RegisterSimulation<SimulationBruteForce>("Brute Force Algortithm");
}

void SimulationLayer::OnEvent(Event& event)
{
	if (p_currentSimulation) {
		p_currentSimulation->OnEvent(event);
	}
}

void SimulationLayer::OnUpdate(float timestep)
{
	if (p_currentSimulation) {
		p_currentSimulation->OnUpdate(timestep);
	}
}

void SimulationLayer::OnRender(Renderer& renderer)
{
	if (p_currentSimulation) {
		p_currentSimulation->OnRender(renderer);
	}
}

void SimulationLayer::OnImGuiRender()
{
	ImGui::Begin("Simulations");
	for (std::pair<std::string, std::function<Simulation* ()>>& simulation : m_simulations) {
		if (ImGui::Button(simulation.first.c_str())) {
			delete p_currentSimulation;
			p_currentSimulation = simulation.second();
		}
	}
	ImGui::End();
	if (p_currentSimulation) {
		p_currentSimulation->OnImGuiRender();
	}
}
