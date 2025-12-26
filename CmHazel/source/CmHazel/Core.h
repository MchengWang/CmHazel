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
