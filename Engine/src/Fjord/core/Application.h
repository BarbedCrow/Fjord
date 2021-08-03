#pragma once

#include <vector>

#include "entt/entt.hpp"

#include "Core.h"
#include "Window.h"
#include "Fjord/ECS/Systems/GameSystem.h"

namespace Fjord
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Start();
		void Update();
		bool Close();

		Window* GetWindow() const { return m_Window.get(); }
		inline static Application& Get() { return *s_Instance; }
	protected:
		virtual void UpdateInternal() = 0;
	protected:
		std::vector<Ref<GameSystem>> m_Systems;
	private:
		Scope<Window> m_Window;

		bool m_Running = false;

		static Application* s_Instance;
	};

	Application* CreateApplication();
}

