#include "cmzpch.h"
#include "CmHazel/Renderer/Framebuffer.h"

#include "CmHazel/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace CmHazel
{

	Shared<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    CM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateShared<OpenGLFramebuffer>(spec);
		}

		CM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}