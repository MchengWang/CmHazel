#pragma once

#include <utility>

#include "CmHazel/Core/Base.h"
#include "CmHazel/Core/KeyCodes.h"
#include "CmHazel/Core/MouseCodes.h"

namespace CmHazel
{

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);
		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();

	};

}