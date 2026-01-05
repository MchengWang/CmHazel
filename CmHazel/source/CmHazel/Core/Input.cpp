#include "cmzpch.h"
#include "CmHazel/Core/Input.h"

#ifdef CM_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsInput.h"
#endif // CM_PLATFORM_WINDOWS

namespace CmHazel
{

	Unique<Input> Input::s_Instance = Input::Create();

	Unique<Input> Input::Create()
	{
#ifdef CM_PLATFORM_WINDOWS
		return CreateUnique<WindowsInput>();
#else
		CM_CORE_ASSERT(false, "Unkown platform!");
		return nullptr
#endif // CM_PLATFORM_WINDOWS

	}

}