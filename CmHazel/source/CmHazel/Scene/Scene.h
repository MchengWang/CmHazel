#pragma once

#include "entt.hpp"

#include "CmHazel/Core/Timestep.h"

namespace CmHazel
{

	class Scene
	{
	public:
		Scene();
		~Scene();

		entt::entity CreateEntity();

		// ¡Ÿ ±
		entt::registry& Reg() { return  m_Registry; }

		void OnUpdate(Timestep ts);

	private:
		entt::registry m_Registry;

	};

}