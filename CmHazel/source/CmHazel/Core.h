#pragma once

#ifdef CM_PLATFORM_WINDOWS
	#if CM_DYNAMIC_LINK
		#ifdef CM_BUILD_DLL
			#define CMHAZEL_API __declspec(dllexport)
		#else
			#define CMHAZEL_API __declspec(dllimport)
		#endif // CM_BUILD_DLL
	#else
		#define CMHAZEL_API
	#endif // CM_DYNAMIC_LINK
#else
	#error CmHazel only supports Windows!
#endif // CM_PLATFORM_WINDOWS

#ifdef CM_DEBUG
	#define CM_ENABLE_ASSERTS
#endif // CM_DEBUG


#ifdef CM_ENABLE_ASSERTS
	#define CM_ASSERT(x, ...) { if(!(x)) { CM_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define CM_CORE_ASSERT(x, ...) { if(!(x)) { CM_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define CM_ASSERT(x, ...)
	#define CM_CORE_ASSERT(x, ...)
#endif // CM_ENABLE_ASSERTS


#define BIT(x) (1 << x)

#define CM_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)