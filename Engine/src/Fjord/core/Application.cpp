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
		m_Window = Window::Create("FJORD", 1280, 720);

		ImGuiSystem::Init(m_Window->GetNativeWindow());

		m_Window->OnWindowClose->AddListener(BIND_EVENT_HANDLER_0(Application::HandleOnWindowClose));
		m_Window->OnWindowResize->AddListener(BIND_EVENT_HANDLER_2(Application::HandleOnWindowResize));
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
			for (auto sys : m_Systems)
			{
				if (sys->IsActive()) sys->Update();
			}

			ImGuiSystem::End();
		}
	}

	bool Application::HandleOnWindowClose()
	{
		m_Running = false;
		return true;
	}

	bool Application::HandleOnWindowResize(uint32_t width, uint32_t height)
	{
		FJORD_CORE_INFO("Resize window ({0}, {0})", width, height);
		return false;
	}
}