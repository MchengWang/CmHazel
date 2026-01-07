#pragma once

#include "CmHazel/Core/Base.h"
#include "CmHazel/Core/Log.h"
#include <filesystem>

#ifdef CM_ENABLE_ASSERTS

	// 或者我们可以对“WITH_MSG”和“NO_MSG”都使用相同的“默认”消息，
	// 并通过连接格式字符串来支持自定义格式，而不是将格式包含在默认消息中
	#define CM_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { CM##type##ERROR(msg, __VA_ARGS__); CM_DEBUGBREAK(); } }
	#define CM_INTERNAL_ASSERT_WITH_MSG(type, check, ...) CM_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define CM_INTERNAL_ASSERT_NO_MSG(type, check) CM_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", CM_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define CM_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define CM_INTERNAL_ASSERT_GET_MACRO(...) CM_EXPAND_MACRO( CM_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, CM_INTERNAL_ASSERT_WITH_MSG, CM_INTERNAL_ASSERT_NO_MSG) )

	// 目前至少接受条件参数，另一个参数（消息）为可选
	#define CM_ASSERT(...) CM_EXPAND_MACRO( CM_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define CM_CORE_ASSERT(...) CM_EXPAND_MACRO( CM_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
	#define CM_ASSERT(...)
	#define CM_CORE_ASSERT(...)
#endif // CM_ENABLE_ASSERTS