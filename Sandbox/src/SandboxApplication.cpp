#include <Fjord.h>
#include <Fjord/core/EntryPoint.h>

#include <Fjord/Render/Buffer.h>
#include <Fjord/Render/Shader.h>
#include <Fjord/Render/VertexArray.h>

#include "Fjord/ECS/Systems/EditorCameraControllerSystem.h"
#include <Fjord/ECS/Systems/RenderSystem.h>
#include <Fjord/ECS/Components/Components.h>

#include <Fjord/core/Input.h>

class Sandbox : public Fjord::Application
{
public:
	Sandbox()
	{
		m_Systems.push_back(Fjord::CreateRef<Fjord::EditorCameraControllerSystem>(&m_Registry));
		auto renderSys = Fjord::CreateRef<Fjord::RenderSystem>(&m_Registry);
		m_Systems.push_back(renderSys);

		float vertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
		};

		auto vBuffer = Fjord::CreateRef<Fjord::VertexBuffer>(vertices, sizeof(vertices));
		Fjord::BufferLayout layout = {
			{Fjord::ShaderDataType::Float3, "a_Position"},
		};
		vBuffer->SetLayout(layout);

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
		auto iBuffer = Fjord::CreateRef<Fjord::IndexBuffer>(indices, 6);

		auto vertexArray = Fjord::CreateRef<Fjord::VertexArray>();
		vertexArray->AddVertexBuffer(vBuffer);
		vertexArray->SetIndexBuffer(iBuffer);

		auto shader = Fjord::CreateRef <Fjord::Shader>("assets/shaders/FlatColorShader.glsl");
		
		//for future camera creation check that there is no active camera
		auto cameraEntt = m_Registry.create();
		m_Registry.emplace<Fjord::TransformComponent>(cameraEntt);
		m_Registry.emplace<Fjord::CameraComponent>(cameraEntt, GetWindow()->GetAspectRatio());

		auto cubeEntt = m_Registry.create();
		m_Registry.emplace<Fjord::TransformComponent>(cubeEntt);
		m_Registry.emplace<Fjord::RenderComponent>(cubeEntt, vertexArray, shader);
	}

	~Sandbox()
	{

	}
};

Fjord::Application* Fjord::CreateApplication()
{
	return new Sandbox();
}