#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace CmHazel
{

	class CMHAZEL_API Log
	{
	public:
		static void Init();
		
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// 核心日志宏
#define CM_CORE_TRACE(...)   ::CmHazel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CM_CORE_INFO(...)    ::CmHazel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CM_CORE_WARN(...)    ::CmHazel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CM_CORE_ERROR(...)   ::CmHazel::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CM_CORE_FATAL(...)   ::CmHazel::Log::GetCoreLogger()->fatal(__VA_ARGS__)


// 客户端日志宏
#define CM_TRACE(...)        ::CmHazel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CM_INFO(...)         ::CmHazel::Log::GetClientLogger()->info(__VA_ARGS__)
#define CM_WARN(...)         ::CmHazel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CM_ERROR(...)        ::CmHazel::Log::GetClientLogger()->error(__VA_ARGS__)
#define CM_FATAL(...)        ::CmHazel::Log::GetClientLogger()->fatal(__VA_ARGS__)