#include "fjordpch.h"
#include "Application.h"

#include <GLFW/glfw3.h>

#include "Fjord/core/Log.h"
#include "Fjord/ImGui/ImGuiSystem.h"
#include "Fjord/core/Time.h"

namespace Fjord
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;
		Log::Init();
		m_Window = Window::Create("FJORD", 1920, 1080);

		ImGuiSystem::Init(m_Window->GetNativeWindow());

		m_Window->OnWindowClose->AddListener(BIND_EVENT_HANDLER_0(Application::Close));
	}

	Application::~Application()
	{
		ImGuiSystem::Terminate();
	}

	void Application::Start()
	{
		m_Running = true;
		for (auto sys : m_Systems)
		{
			sys->Activate();
		}
	}

	void Application::Update()
	{
		while (m_Running)
		{
			Time::SetTime(glfwGetTime());
			m_Window->Update();
			ImGuiSystem::Begin();
			UpdateInternal();
			for (auto sys : m_Systems)
			{
				if (sys->IsActive()) sys->Update();
			}
			ImGuiSystem::End();
		}
	}

	bool Application::Close()
	{
		m_Running = false;
		return true;
	}
}