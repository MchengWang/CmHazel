#pragma once

#include "CMHAZEL.h"

class Sandbox2D : public CmHazel::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(CmHazel::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(CmHazel::Event& e) override;

private:
	CmHazel::OrthographicCameraController m_CameraController;

	// temp
	CmHazel::Shared<CmHazel::VertexArray> m_SquareVA;
	CmHazel::Shared<CmHazel::Shader> m_FlatColorShader;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};