#pragma once

#include "Core.h"

namespace Fjord
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Update();

		inline static Application& Get() { return *s_Instance; }
	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();
}

