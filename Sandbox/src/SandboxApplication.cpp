#include "SandboxApplication.h"

#include <Fjord/core/EntryPoint.h>

Sandbox::Sandbox()
{
	
}

Sandbox::~Sandbox()
{

}

void Sandbox::UpdateInternal()
{

}

Fjord::Application* Fjord::CreateApplication()
{
	return new Sandbox();
}