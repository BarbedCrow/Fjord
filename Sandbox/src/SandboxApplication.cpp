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

	void UpdateInternal() override
	{

	}
};

Fjord::Application* Fjord::CreateApplication()
{
	return new Sandbox();
}