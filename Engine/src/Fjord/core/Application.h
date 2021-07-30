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

		Window* GetWindow() const { return m_Window.get(); }
		inline static Application& Get() { return *s_Instance; }
	private:
		virtual bool HandleOnWindowClose();
		virtual bool HandleOnWindowResize(uint32_t width, uint32_t height);
	private:
		Scope<Window> m_Window;

		bool m_Running = true;

		static Application* s_Instance;
	};

	Application* CreateApplication();
}

