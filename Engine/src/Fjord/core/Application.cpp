#include "fjordpch.h"
#include "Application.h"

#include <GLFW/glfw3.h>

#include "Fjord/core/Log.h"
#include "Fjord/ImGui/ImGuiSystem.h"
#include "Fjord/core/Time.h"

namespace Fjord
{
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		s_instance = this;
		Log::Init();
		m_window = Window::Create("FJORD", 1920, 1080);

		ImGuiSystem::Init(m_window->GetNativeWindow());

		m_window->OnWindowClose->AddListener(BIND_EVENT_HANDLER_0(Application::Close));
	}

	Application::~Application()
	{
		ImGuiSystem::Terminate();
	}

	void Application::Start()
	{
		for(auto flow : m_flows)
		{
			flow->Start();
		}
		m_running = true;
	}

	void Application::Update()
	{
		while (m_running)
		{
			Time::SetTime(glfwGetTime());
			m_window->Update();
			ImGuiSystem::Begin();
			UpdateInternal();
			for(auto flow : m_flows)
			{
				flow->Update();
			}
			ImGuiSystem::End();
		}
	}

	bool Application::Close()
	{
		for(auto flow : m_flows)
		{
			flow->Close();
		}
		m_running = false;
		return true;
	}
}