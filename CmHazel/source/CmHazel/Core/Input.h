#pragma once

#include <utility>

#include <glm/glm.hpp>

#include "CmHazel/Core/KeyCodes.h"
#include "CmHazel/Core/MouseCodes.h"

namespace CmHazel
{

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);
		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();

	};

}