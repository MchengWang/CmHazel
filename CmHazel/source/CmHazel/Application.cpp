#include "Application.h"

#include "CmHazel/Events/ApplicationEvent.h"
#include "CmHazel/Log.h"

namespace CmHazel
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			CM_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			CM_TRACE(e);
		}
		while (true);
	}

}