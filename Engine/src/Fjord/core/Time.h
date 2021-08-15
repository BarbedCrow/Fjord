#pragma once

#include <GLFW/glfw3.h>

namespace Fjord
{
	class Time
	{
		friend class Application;
	public:

		static float GetTime() { return glfwGetTime(); }
		
		static float GetDeltaTime() { return glfwGetTime() - s_Time; }

	private:
		static float s_Time;
		static float s_DeltaTime;

		static void SetTime(float time)
		{
			s_DeltaTime = time - s_Time;
			s_Time = time;
		}
	};
}

