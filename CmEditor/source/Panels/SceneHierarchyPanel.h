#pragma once

#include "CmHazel/Core/Base.h"
#include "CmHazel/Scene/Scene.h"
#include "CmHazel/Scene/Entity.h"

namespace CmHazel
{

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Shared<Scene>& scene);

		void SetContext(const Shared<Scene>& scene);

		void OnImGuiRender();

		Entity GetSelectedEntity() const { return m_SelectionContext; }
		void SetSelectedEntity(Entity entity);

	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);

	private:
		Shared<Scene> m_Context;
		Entity m_SelectionContext;

	};

}