#include "cmzpch.h"
#include "CmHazel/Renderer/VertexArray.h"

#include "CmHazel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace CmHazel
{

	Shared<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: CM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateShared<OpenGLVertexArray>();
		}

		CM_CORE_ASSERT(false, "Unkown RendererAPI!");
		return nullptr;
	}

}