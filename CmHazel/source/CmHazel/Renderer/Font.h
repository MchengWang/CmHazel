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

		const MSDFData* GetMSDFData() const { return m_Data; }
		Shared<Texture2D> GetAtlasTexture() const { return m_AtlasTexture; }

		static Shared<Font> GetDefault();

	private:
		MSDFData* m_Data;
		Shared<Texture2D> m_AtlasTexture;

	};

}