#pragma once

#include <GLRenderer.h>

#include "Circle.h"

class Simulation
{
public:
	Simulation();
	~Simulation();

	virtual void OnUpdate(float timestep);
	virtual void OnFixedUpdate() {}
	virtual void OnEvent(Event& event);
	virtual void OnRender(Renderer& renderer);
	virtual void OnGizmoRender(Renderer& renderer) {}
	virtual void OnImGuiRender() {}

	void CreateCircle();

	inline const int GetCircleCount() const { return m_circleCount; }
protected:
	OrthographicCameraController m_cameraController;
	std::vector<Circle> m_circles;
protected:
	VertexArray m_vao;
	VertexBuffer m_vbo;
	IndexBuffer m_ibo;
	Shader* p_shader;
	Texture* p_texture;
	Texture* p_squareTexture;
	ImVec4 m_clearColor;
	ImVec4 m_imageColor;
protected:
	float m_ms;
	float m_timestep;
	float m_fixedTimestep = 1.0f / 40.0f;
	float m_elapsedTime = 0.0f;
private:
	bool OnShowGizmosInput(MouseButtonPressedEvent& event);
	bool OnFreezeTime(KeyPressedEvent& event);
private:
	int m_circleCount = 0;
	bool m_showGizmos = false;
	bool m_freezeTime = false;
};