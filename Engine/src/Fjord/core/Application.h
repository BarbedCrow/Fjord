#pragma once

#include "Core.h"
#include "Window.h"

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
		Scope<Window> m_Window;

		static Application* s_Instance;
	};

	Application* CreateApplication();
}

