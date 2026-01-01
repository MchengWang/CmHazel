#include "cmzpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace CmHazel
{

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}