#pragma once

#include <vector>

#include "entt/entt.hpp"

#include "Core.h"
#include "Window.h"
#include "Flow.h"

/*
 * This class acts as a main point of your application's start.
 * It allows you to specify the flows you want to use in your
 * app and how you want to handle switching between those flows.
 *
 * To use it in your project just create a child class inside your
 * project and override an UpdateInternal() method and also
 * override CreateApplication() method to make sure that EntryPoint can
 * actually create your Application class implementation
 */
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

		Window* GetWindow() const { return m_window.get(); }
		inline static Application& Get() { return *s_instance; }

	protected:
		virtual void UpdateInternal() = 0;

	protected:
		std::vector<Ref<Flow>> m_flows;
	
	private:
		Scope<Window> m_window;

		bool m_running = false;
		
		static Application* s_instance;
	};

	Application* CreateApplication();
	void GenerateMetaData();
}

