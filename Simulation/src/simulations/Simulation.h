#pragma once

#include <GLRenderer.h>

#include "Circle.h"

class Simulation
{
public:
	Simulation();
	~Simulation();

	virtual void OnUpdate(float timestep) {}
	virtual void OnEvent(Event& event);
	virtual void OnRender(Renderer& renderer);
	virtual void OnImGuiRender() {}
protected:
	OrthographicCameraController m_cameraController;
	std::vector<Circle> m_circles;
private:
	VertexArray m_vao;
	VertexBuffer m_vbo;
	IndexBuffer m_ibo;
	Shader* p_shader;
	Texture* p_texture;
	ImVec4 m_clearColor;
	ImVec4 m_imageColor;
};