#pragma once

#include <memory>

// 使用预定义宏进行平台检测
#ifdef _WIN32
	/* Windows x64/x86 */
	#ifdef _WIN64
		/* Windows x64 */
		#define CM_PLATFORM_WINDOWS
	#else
		/* Windows x86 */
		#error "x86 build are not supported!"
	#endif // _WIN64
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	/*
	* TARGET_OS_MAC 在所有平台上都存在，所以我们必须检查所有平台（按此顺序）
	* 以确保我们运行的是 MAC，而不是其他 Apple 平台
	*/
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define CM_PLATFORM_IOS
	#elif TARGET_OS_MAC == 1
		#define CM_PLATFORM_MACOS
	#else
		#error "Unkown Apple platform!"
	#endif // TARGET_IPHONE_SIMULATOR == 1
/*
* 我们在检查 __linux__ 之前也必须检查 __ANDROID__，
* 因为 Android 是基于 Linux 内核的 *它定义了 __linux__
*/
#elif defined(__ANDROID__)
	#define CM_PLATFORM_LINUX
	#error "Android is not supported!"
#elif defined(__linux__)
	#define CM_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	/* 未知的编译器/平台 */
	#error "Unkown platform!"
#endif // _WIN32

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

#define CM_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

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