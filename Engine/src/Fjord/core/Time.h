#pragma once

namespace Fjord
{
	class Time
	{
		friend class Application;
	public:

		static float GetTime() { return s_Time; }
		static float GetDeltaTime() { return s_DeltaTime; }

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

