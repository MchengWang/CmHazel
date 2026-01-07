#pragma once

#include <string>

namespace CmHazel
{

	class FileDialogs
	{
	public:
		// 如果取消，这些将返回空字符串
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);
	};

}