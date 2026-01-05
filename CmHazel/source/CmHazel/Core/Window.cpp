#include "cmzpch.h"
#include "CmHazel/Core/Window.h"

#ifdef CM_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"
#endif // CM_PLATFORM_WINDOWS

namespace CmHazel
{

	Unique<Window> Window::Create(const WindowProps& props)
	{
#ifdef CM_PLATFORM_WINDOWS
		return CreateUnique<WindowsWindow>(props);
#else
		CM_CORE_ASSERT(false, "Unkown platform!");
		return nullptr;
#endif // CM_PLATFORM_WINDOWS

	}

}