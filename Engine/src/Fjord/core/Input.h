#pragma once

#include "Core.h"
#include "KeyCodes.h"
#include "MouseButtonCodes.h"

namespace Fjord
{
	class Input
	{
	public:
		static bool IsKeyPressed(int code);

		static bool IsMouseButtonPressed(int code);
		static std::pair<float, float> GetMousePos();
		static float GetMouseX();
		static float GetMouseY();
	};
}