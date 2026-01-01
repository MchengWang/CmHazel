#include "cmzpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace CmHazel
{

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: CM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}

		CM_CORE_ASSERT(false, "Unkown RendererAPI!");
		return nullptr;
	}

}