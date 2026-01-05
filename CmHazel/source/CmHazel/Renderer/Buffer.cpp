#include "cmzpch.h"
#include "CmHazel/Renderer/Buffer.h"

#include "CmHazel/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace CmHazel
{

	Shared<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    CM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateShared<OpenGLVertexBuffer>(size);
		}

		CM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Shared<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    CM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateShared<OpenGLVertexBuffer>(vertices, size);
		}

		CM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Shared<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    CM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateShared<OpenGLIndexBuffer>(indices, size);
		}

		CM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}