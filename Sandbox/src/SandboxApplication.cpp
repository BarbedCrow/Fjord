#include <Fjord.h>
#include <Fjord/core/EntryPoint.h>

#include <Fjord/Render/Buffer.h>
#include <Fjord/Render/Shader.h>
#include <Fjord/Render/VertexArray.h>

class Sandbox : public Fjord::Application
{
public:
	Sandbox()
	{
		//Fjord::Shader("assets/shaders/FlatColorShader.glsl");

	}

	~Sandbox()
	{

	}
private:
	//m_Shader
};

Fjord::Application* Fjord::CreateApplication()
{
	return new Sandbox();
}