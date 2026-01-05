#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{ }

void Sandbox2D::OnAttach()
{
	CM_PROFILE_FUNCTION();

	m_CheckerboardTexture = CmHazel::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	CM_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(CmHazel::Timestep ts)
{
	CM_PROFILE_FUNCTION();

	// ¸üÐÂ
	m_CameraController.OnUpdate(ts);

	// äÖÈ¾
	{
		CM_PROFILE_SCOPE("Renderer Prep");
		CmHazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		CmHazel::RenderCommand::Clear();
	}
	
	{
		CM_PROFILE_SCOPE("Renderer Draw");
		CmHazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
		CmHazel::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		// CmHazel::Renderer2D::DrawQuad(m_CameraController.GetCamera().GetPosition(), {0.8f, 0.8f}, {0.8f, 0.2f, 0.3f, 1.0f});
		CmHazel::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		CmHazel::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);
		CmHazel::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}

void Sandbox2D::OnEvent(CmHazel::Event& e)
{
	m_CameraController.OnEvent(e);
}