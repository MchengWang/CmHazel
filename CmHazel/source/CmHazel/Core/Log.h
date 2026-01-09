#pragma once

#include "CmHazel/Core/Base.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace CmHazel
{

	class Log
	{
	public:
		static void Init();
		
		inline static Shared<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Shared<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static Shared<spdlog::logger> s_CoreLogger;
		static Shared<spdlog::logger> s_ClientLogger;
	};

}

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
	return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
	return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternio)
{
	return os << glm::to_string(quaternio);
}

// 核心日志宏
#define CM_CORE_TRACE(...)          ::CmHazel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CM_CORE_INFO(...)           ::CmHazel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CM_CORE_WARN(...)           ::CmHazel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CM_CORE_ERROR(...)          ::CmHazel::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CM_CORE_CRITICAL(...)       ::CmHazel::Log::GetCoreLogger()->critical(__VA_ARGS__)
								    
								    
// 客户端日志宏				        
#define CM_TRACE(...)               ::CmHazel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CM_INFO(...)                ::CmHazel::Log::GetClientLogger()->info(__VA_ARGS__)
#define CM_WARN(...)                ::CmHazel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CM_ERROR(...)               ::CmHazel::Log::GetClientLogger()->error(__VA_ARGS__)
#define CM_CRITICAL(...)            ::CmHazel::Log::GetClientLogger()->critical(__VA_ARGS__)