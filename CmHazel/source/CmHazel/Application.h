#pragma once

#include "Core.h"

#include "Window.h"
#include "CmHazel/LayerStack.h"
#include "CmHazel/Events/Event.h"
#include "CmHazel/Events/ApplicationEvent.h"

#include "CmHazel/ImGui/ImGuiLayer.h"

namespace CmHazel
{

	class CMHAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
		
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;

	private:
		static Application* s_Instance;

	};

	// 在客户端定义
	Application* CreateApplication();

}