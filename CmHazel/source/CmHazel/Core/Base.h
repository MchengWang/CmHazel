#pragma once

#include <memory>

#include "CmHazel/Core/PlatformDetection.h"

#ifdef CM_DEBUG
	#define CM_ENABLE_ASSERTS
#endif // CM_DEBUG

// 让这个宏除了条件之外不接受任何参数
#ifdef CM_ENABLE_ASSERTS
	#define CM_ASSERT(x, ...) { if(!(x)) { CM_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define CM_CORE_ASSERT(x, ...) { if(!(x)) { CM_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define CM_ASSERT(x, ...)
	#define CM_CORE_ASSERT(x, ...)
#endif // CM_ENABLE_ASSERTS


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