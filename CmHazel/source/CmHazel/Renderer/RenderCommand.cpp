#include "cmzpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace CmHazel
{

	Unique<RendererAPI> RenderCommand::s_RendererAPI = CreateUnique<OpenGLRendererAPI>();

}