#include "fjordpch.h"
#include "Application.h"

#include "Fjord/core/Log.h"
#include "Fjord/ImGui/ImGuiSystem.h"

//REMOVE
#include <glad/glad.h>
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

namespace Fjord
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;
		Log::Init();
		m_Window = Window::Create("FJORD", 1280, 720);

		ImGuiSystem::Init(m_Window->GetNativeWindow());

		m_Window->OnWindowClose->AddListener(BIND_EVENT_HANDLER_0(Application::HandleOnWindowClose));
		m_Window->OnWindowResize->AddListener(BIND_EVENT_HANDLER_2(Application::HandleOnWindowResize));


		//TEST RENDER SETUP; REMOVE
		//Vertex Buffer
		float vertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
		};

		auto vBuffer = CreateRef<VertexBuffer>(vertices, sizeof(vertices));
		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
		};
		vBuffer->SetLayout(layout);

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
		auto iBuffer = CreateRef<IndexBuffer>(indices, 6);

		m_VertexArray = CreateRef<VertexArray>();
		m_VertexArray->AddVertexBuffer(vBuffer);
		m_VertexArray->SetIndexBuffer(iBuffer);
	}

	Application::~Application()
	{
		ImGuiSystem::Terminate();
	}

	void Application::Update()
	{
		while (m_Running)
		{
			m_Window->Update();
			ImGuiSystem::Begin();

			//TEST RENDER; REMOVE LATER
			//Imgui
			ImGui::Begin("TEST");
			ImGui::ColorPicker4("Color", glm::value_ptr(testColor));
			ImGui::End();
			
			//Render
			m_VertexArray->Bind();
			glClearColor(testColor.r, testColor.g, testColor.b, testColor.a);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
			//TEST RENDER//////////////

			ImGuiSystem::End();
		}
	}

	bool Application::HandleOnWindowClose()
	{
		m_Running = false;
		return true;
	}

	bool Application::HandleOnWindowResize(uint32_t width, uint32_t height)
	{
		FJORD_CORE_INFO("Resize window ({0}, {0})", width, height);
		return false;
	}
}