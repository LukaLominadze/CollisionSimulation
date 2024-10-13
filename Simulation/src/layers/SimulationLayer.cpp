#include "SimulationLayer.h"

#include "simulations/SimulationBruteForce.h"
#include "simulations/SimulationSpacePartition.h"
#include "simulations/SimulationQuadTree.h"

void SimulationLayer::OnAttach()
{
	RegisterSimulation<SimulationBruteForce>("Brute Force Algortithm");
	RegisterSimulation<SimulationSpacePartition>("Space Partitioning Algorithm");
	RegisterSimulation<SimulationQuadTree>("Quad Tree Algorithm");
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
	ImGui::Begin("Controls");
	ImGui::Text("F11 - Fullscreen");
	ImGui::Text("Mouse Scroll - Zoom I/O");
	ImGui::Text("WASD - Move");
	ImGui::Text("Right Click - Toggle Gizmos");
	ImGui::Text("Enter - Spawn Circles");
	ImGui::Text("Space - Pause Simulation");
	ImGui::End();
	if (p_currentSimulation) {
		p_currentSimulation->OnImGuiRender();
	}
}
