#include "cmzpch.h"
#include "CmHazel/Renderer/RenderCommand.h"

namespace CmHazel
{

	Unique<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}