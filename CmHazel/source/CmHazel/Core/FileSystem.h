#pragma once

#include "CmHazel/Core/Buffer.h"

namespace CmHazel
{

	class FileSystem
	{
	public:
		// 移动到文件系统类
		static Buffer ReadFileBinary(const std::filesystem::path& filepath);

	};

}