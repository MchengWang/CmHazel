#include "cmzpch.h"
#include "CmHazel/Renderer/GraphicsContext.h"

#include "CmHazel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace CmHazel
{

	Unique<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    CM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateUnique<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		CM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}