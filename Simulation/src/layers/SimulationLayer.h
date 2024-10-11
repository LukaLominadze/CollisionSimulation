#pragma once

#include <GLRenderer.h>

class SimulationLayer : public Layer
{
public:
	SimulationLayer();
	virtual ~SimulationLayer() override;

	void OnAttach() override;
	void OnEvent(Event& event) override;
	void OnUpdate(float timestep) override;
	void OnRender(Renderer& renderer) override;
	void OnImGuiRender() override;
private:
	VertexArray m_vao;
	VertexBuffer m_vbo;
	IndexBuffer m_ibo;
	Shader* p_shader;
	Texture* p_texture;
	ImVec4 m_clearColor;
	ImVec4 m_imageColor;

	OrthographicCameraController m_cameraController;
private:
	struct Circle {
		glm::vec3 Position;
		glm::vec3 Scale;
		ImVec4 Color;
	};

	std::vector<Circle> m_circles;
};