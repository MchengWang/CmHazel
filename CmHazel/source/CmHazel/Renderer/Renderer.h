#pragma once

#include "CmHazel/Renderer/RenderCommand.h"

#include "CmHazel/Renderer/OrthographicCamera.h"
#include "CmHazel/Renderer/Shader.h"

namespace CmHazel
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Shared<Shader>& shader, const Shared<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static Unique<SceneData> s_SceneData;
	};

}