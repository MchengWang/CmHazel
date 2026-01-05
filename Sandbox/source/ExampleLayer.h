#pragma once

#include "CMHAZEL.h"

class ExampleLayer : public CmHazel::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;
	
	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(CmHazel::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(CmHazel::Event& e) override;

private:
	CmHazel::ShaderLibrary m_ShaderLibrary;
	CmHazel::Shared<CmHazel::Shader> m_Shader;
	CmHazel::Shared<CmHazel::VertexArray> m_VertexArray;

	CmHazel::Shared<CmHazel::Shader> m_FlatColorShader;
	CmHazel::Shared<CmHazel::VertexArray> m_SquareVA;

	CmHazel::Shared<CmHazel::Texture2D> m_Texture, m_PhtatoLogoTexture;

	CmHazel::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};