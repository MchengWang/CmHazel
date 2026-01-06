#pragma once

#include "CMHAZEL.h"

namespace CmHazel
{

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;

	private:
		OrthographicCameraController m_CameraController;

		// temp
		Shared<VertexArray> m_SquareVA;
		Shared<Shader> m_FlatColorShader;
		Shared<Framebuffer> m_Framebuffer;

		Shared<Scene> m_ActiveScene;
		entt::entity m_SquareEntity;

		Shared<Texture2D> m_CheckerboardTexture;

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };

		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	};

}