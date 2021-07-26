#include <Fjord.h>
#include <Fjord/core/EntryPoint.h>

class Sandbox : public Fjord::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Fjord::Application* Fjord::CreateApplication()
{
	return new Sandbox();
}