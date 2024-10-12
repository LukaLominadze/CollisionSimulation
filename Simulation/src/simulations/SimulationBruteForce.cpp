#include "SimulationBruteForce.h"

void SimulationBruteForce::OnUpdate(float timestep)
{
    m_cameraController.OnUpdate(timestep);
    for (int i = 0; i < m_circles.size(); i++) {
        m_circles[i].OnUpdate(timestep);
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
}
