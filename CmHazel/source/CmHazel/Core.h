#pragma once

#ifdef CM_PLATFORM_WINDOWS
	#ifdef CM_BUILD_DLL
		#define CMHAZEL_API __declspec(dllexport)
	#else
		#define CMHAZEL_API __declspec(dllimport)
	#endif // CM_BUILD_DLL
#else
	#error CmHazel only supports Windows!
#endif // CM_PLATFORM_WINDOWS

#ifdef CM_ENABLE_ASSERTS
	#define CM_ASSERT(x, ...) { if(!(x)) { CM_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define CM_CORE_ASSERT(x, ...) { if(!(x)) { CM_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define CM_ASSERT(x, ...)
	#define CM_CORE_ASSERT(x, ...)
#endif // CM_ENABLE_ASSERTS


#define BIT(x) (1 << x)