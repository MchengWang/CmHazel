#include "cmzpch.h"
#include "CmHazel/Renderer/Texture.h"

#include "CmHazel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace CmHazel
{

	Shared<Texture2D> Texture2D::Create(const TextureSpecification& specification)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: CM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateShared<OpenGLTexture2D>(specification);
		}

		CM_CORE_ASSERT(false, "Unkown RendererAPI!");
		return nullptr;
	}

	Shared<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: CM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateShared<OpenGLTexture2D>(path);
		}

		CM_CORE_ASSERT(false, "Unkown RendererAPI!");
		return nullptr;
	}

}