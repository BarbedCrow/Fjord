#pragma once

#include "Application.h"

extern Fjord::Application* Fjord::CreateApplication();
extern void Fjord::GenerateMetaData();

int main()
{
	Fjord::GenerateMetaData();
	Fjord::Application* app = Fjord::CreateApplication();
	app->Start();
	app->Update();
	delete app;
}
