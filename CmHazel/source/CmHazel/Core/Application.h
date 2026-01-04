#pragma once

#include "CmHazel/Core/Core.h"

#include "CmHazel/Core/Window.h"
#include "CmHazel/Core/LayerStack.h"
#include "CmHazel/Events/Event.h"
#include "CmHazel/Events/ApplicationEvent.h"

#include "CmHazel/Core/Timestep.h"

#include "CmHazel/ImGui/ImGuiLayer.h"

namespace CmHazel
{

	class Application
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
		bool OnWindowResize(WindowResizeEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;

		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;

	};

	// 在客户端定义
	Application* CreateApplication();

}