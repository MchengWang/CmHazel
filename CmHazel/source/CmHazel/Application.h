#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "CmHazel/Events/ApplicationEvent.h"

#include "Window.h"

namespace CmHazel
{

	class CMHAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

	};

	// 在客户端定义
	Application* CreateApplication();

}