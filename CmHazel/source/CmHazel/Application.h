#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace CmHazel
{

	class CMHAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// 在客户端定义
	Application* CreateApplication();

}