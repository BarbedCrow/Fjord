#include "Application.h"

namespace Fjord
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;
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