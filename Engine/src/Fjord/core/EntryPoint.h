#pragma once

#include "Application.h"

extern Fjord::Application* Fjord::CreateApplication();

int main()
{
	Fjord::Application* app = Fjord::CreateApplication();
	app->Update();
	delete app;
}
