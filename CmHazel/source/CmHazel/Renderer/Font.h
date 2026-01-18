#pragma once

#include <filesystem>

#include "CmHazel/Core/Base.h"
#include "CmHazel/Renderer/Texture.h"

namespace CmHazel
{

	struct MSDFData;

	class Font
	{
	public:
		Font(const std::filesystem::path& font);
		~Font();

		Shared<Texture2D> GetAtlasTexture() const { return m_AtlasTexture; }

	private:
		MSDFData* m_Data;
		Shared<Texture2D> m_AtlasTexture;

	};

}