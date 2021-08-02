#include <Fjord.h>
#include <Fjord/core/EntryPoint.h>

class Sandbox : public Fjord::Application
{
public:
	Sandbox()
	{
		m_Systems.push_back(Fjord::CreateRef<Fjord::EditorCameraControllerSystem>(&m_Registry));
		auto renderSys = Fjord::CreateRef<Fjord::RenderSystem>(&m_Registry);
		m_Systems.push_back(renderSys);

		//ENTITIES

		//for future camera creation check that there is no active camera
		auto cameraEntt = m_Registry.create();
		m_Registry.emplace<Fjord::TransformComponent>(cameraEntt);
		m_Registry.emplace<Fjord::CameraComponent>(cameraEntt, GetWindow()->GetAspectRatio());

		float vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		};

		auto vBuffer = Fjord::CreateRef<Fjord::VertexBuffer>(vertices, sizeof(vertices));
		Fjord::BufferLayout layout = {
			{Fjord::ShaderDataType::Float3, "a_Position"},
			{Fjord::ShaderDataType::Float2, "a_TexCoord"},
		};
		vBuffer->SetLayout(layout);

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
		auto iBuffer = Fjord::CreateRef<Fjord::IndexBuffer>(indices, 6);

		auto vertexArray = Fjord::CreateRef<Fjord::VertexArray>();
		vertexArray->AddVertexBuffer(vBuffer);
		vertexArray->SetIndexBuffer(iBuffer);

		//auto shader = Fjord::CreateRef <Fjord::Shader>("assets/shaders/FlatColorShader.glsl");
		auto shader = Fjord::CreateRef <Fjord::Shader>("assets/shaders/TextureShader.glsl");

		auto texture = Fjord::CreateRef<Fjord::Texture2D>("assets/textures/test_texture.png");

		auto cubeEntt = m_Registry.create();
		m_Registry.emplace<Fjord::TransformComponent>(cubeEntt);

		//m_Registry.emplace<Fjord::RenderComponent>(cubeEntt, vertexArray, shader);
		m_Registry.emplace<Fjord::RenderComponent>(cubeEntt, vertexArray, shader, texture);
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