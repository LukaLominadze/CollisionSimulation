#include "SimulationBruteForce.h"

void SimulationBruteForce::OnFixedUpdate()
{
    for (int i = 0; i < m_circles.size(); i++) {
        for (int j = 0; j < i; j++) {
            m_circles[i].Collide(m_circles[j]);
        }
        for (int j = i + 1; j < m_circles.size(); j++) {
            m_circles[i].Collide(m_circles[j]);
        }
    }
}

void SimulationBruteForce::OnImGuiRender()
{
    ImGui::Begin("Stats");

    ImGui::Text("Brute Force Algorithm\n\nThis algorithm loops through \nthe existing objects");
    ImGui::Text("and checks if it is collliding \nwith every other object,");
    ImGui::Text("making this an algorithm \nwith the runtime of O(n(n - 1))\n\n\n");

    ImGui::Text("Algorithm speed");
    ImGui::Text((std::to_string(m_ms) + " ms.").c_str());
    ImGui::Text(("FPS : " + std::to_string(1 / m_timestep)).c_str());
    ImGui::Text(("Circle Count : " + std::to_string(GetCircleCount())).c_str());

    ImGui::End();
}
