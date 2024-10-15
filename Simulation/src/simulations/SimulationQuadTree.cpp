#include "SimulationQuadTree.h"

SimulationQuadTree::SimulationQuadTree()
	:m_capacity(6), m_tree(QuadTree(Boundary(0, 0, 2, 2), m_capacity))
{
}

void SimulationQuadTree::OnFixedUpdate()
{
	m_tree.SetCapacity(m_capacity);
	for (int i = 0; i < m_circles.size(); i++) {
		Boundary circle = Boundary(m_circles[i].m_Position.x, m_circles[i].m_Position.y,
								   m_circles[i].GetRadius(), m_circles[i].GetRadius());
		m_tree.Insert(circle, i);
	}
	std::vector<Boundary> boundaries;
	m_tree.GetBoundaries(boundaries);
	m_boundaries = boundaries;
	for (int i = 0; i < m_circles.size(); i++) {
		std::vector<int> circlesInRange;
		Circle& circle = m_circles[i];
		m_tree.Query(Boundary(circle.m_Position.x, circle.m_Position.y,
					          circle.GetRadius() * 2 + 0.1f, circle.GetRadius() * 2 + 0.1f), circlesInRange);
		for (int otherIndex : circlesInRange) {
			if (otherIndex != i) {
				circle.Collide(m_circles[otherIndex]);
			}
		}
	}
	m_tree.Clear();
}

void SimulationQuadTree::OnGizmoRender(Renderer& renderer)
{
	float b = 1.0f;
	float r = 1.0f;
	for (const Boundary& boundary : m_boundaries) {
		p_shader->SetUniform4f("u_Color", r, 0.0f, b, 1.0f);
		glm::vec3 translation(boundary.x1 + (boundary.x2 - boundary.x1) / 2.0f, boundary.y1 + (boundary.y2 - boundary.y1) / 2.0f, 0.0f);
		glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
		model = glm::scale(model, glm::vec3((boundary.x2 - boundary.x1) * 5, (boundary.y2 - boundary.y1) * 5, 1.0f));
		glm::mat4 mvp = m_cameraController.GetCamera().GetViewProjectionMatrix() * model;
		p_shader->SetUniformMat4f("u_MVP", mvp);

		r -= 0.007f;
		if (r < 0) {
			r = 0.0f;
			r -= 0.005f;
			if (r < 0) {
				r = 0.0f;
			}
		}

		renderer.Draw(m_vao, m_ibo, *p_shader);
	}
}

void SimulationQuadTree::OnImGuiRender()
{
	ImGui::Begin("Stats");

	ImGui::Text("QuadTree Algorithm\n\nWorks best when objects are not\nclumped together!\n");
	ImGui::Text("This algorithm ideally has a \nruntime complexity of O(n)\n");
	ImGui::Text("But in this case, it's \na little worse than O(nlogn)\n\n");

	ImGui::Text("Algorithm speed");
	ImGui::Text((std::to_string(m_ms) + " ms.").c_str());
	ImGui::Text(("FPS : " + std::to_string(1 / m_timestep)).c_str());
	ImGui::Text(("Circle Count : " + std::to_string(GetCircleCount())).c_str());

	ImGui::DragInt("Grid Capacity", &m_capacity, 1); 

	ImGui::End();
}
