#pragma once

#include <memory>

#include "CmHazel/Core/PlatformDetection.h"

#ifdef CM_DEBUG
	#if defined(CM_PLATFORM_WINDOWS)
		#define CM_DEBUGBREAK() __debugbreak()
	#elif defined(CM_PLATFORM_LINUX)
		#include <signal.h>
		#define CM_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif // defined(CM_PLATFORM_WINDOWS)
	#define CM_ENABLE_ASSERTS
#else
	#define CM_DEBUGBREAK()
#endif // CM_DEBUG

#define CM_EXPAND_MACRO(x) x
#define CM_STRINGIFY_MACRO(x) #x


#define BIT(x) (1 << x)

#define CM_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace CmHazel
{

	template <typename T>
	using Unique = std::unique_ptr<T>;

	template <typename T, typename ... Args>
	constexpr Unique<T> CreateUnique(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template <typename T>
	using Shared = std::shared_ptr<T>;

	template <typename T, typename ... Args>
	constexpr Shared<T> CreateShared(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}

#include "CmHazel/Core/Log.h"
#include "CmHazel/Core/Assert.h"