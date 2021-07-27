#include "fjordpch.h"
#include "Application.h"

#include "Fjord/core/Log.h"

namespace Fjord
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;
		Log::Init();
		m_Window = Window::Create("FJORD", 1280, 720);
		m_Window->OnWindowClose->AddListener(BIND_EVENT_HANDLER_0(Application::HandleOnWindowClose));
		m_Window->OnWindowResize->AddListener(BIND_EVENT_HANDLER_2(Application::HandleOnWindowResize));
	}

	Application::~Application()
	{

	}

	void Application::Update()
	{
		while (m_Running)
		{
			m_Window->Update();
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