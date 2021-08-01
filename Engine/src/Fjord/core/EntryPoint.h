#pragma once

#include "Application.h"

extern Fjord::Application* Fjord::CreateApplication();

int main()
{
	Fjord::Application* app = Fjord::CreateApplication();
	app->Start();
	app->Update();
	delete app;
}
