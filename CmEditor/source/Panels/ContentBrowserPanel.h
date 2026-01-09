#pragma once

#include <filesystem>

#include "CmHazel/Renderer/Texture.h"


namespace CmHazel
{

	class ContentBrowserPanel
	{
	public:
		ContentBrowserPanel();

		void OnImGuiRender();

	private:
		std::filesystem::path m_CurrentDirectory;

		Shared<Texture2D> m_DirectoryIcon;
		Shared<Texture2D> m_FileIcon;

	};

}