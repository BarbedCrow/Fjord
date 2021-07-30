#pragma once

namespace Fjord
{
	class ImGuiSystem
	{
	public:
		static void Init(void* window);
		static void Terminate();
		static void Begin();
		static void End();
	private:
		static ImGuiSystem* s_Instance;
	};
}
