#include "cmzpch.h"
#include "UniformBuffer.h"

#include "CmHazel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLUniformBuffer.h"

namespace CmHazel
{

	Shared<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    CM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateShared<OpenGLUniformBuffer>(size, binding);
		}

		CM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;

	}
}