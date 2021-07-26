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
	}

	Application::~Application()
	{

	}

	void Application::Update()
	{
		while (true)
		{

		}
	}

}