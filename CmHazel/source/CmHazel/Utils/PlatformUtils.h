#pragma once

#include <string>
#include <optional>

namespace CmHazel
{

	class FileDialogs
	{
	public:
		// 如果取消，这些将返回空字符串
		static std::optional<std::string> OpenFile(const char* filter);
		static std::optional<std::string> SaveFile(const char* filter);
	};

}