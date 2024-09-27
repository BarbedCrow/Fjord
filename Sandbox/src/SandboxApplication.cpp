#include "SandboxApplication.h"

#include <Fjord/core/EntryPoint.h>

#include <glad/glad.h>
#include <imgui.h>

namespace Fjord
{
	Application* Fjord::CreateApplication()
	{
		return new Sandbox();
	}

	Sandbox::Sandbox()
	{
		m_scene = CreateRef<Scene>();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_vertexArray = CreateRef<VertexArray>();

		//Setup vertex buffer
		auto vBuffer = CreateRef<VertexBuffer>(MAX_VERTEX_COUNT * sizeof(VertexData));
		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"},
		};
		vBuffer->SetLayout(layout);
		m_vertexArray->SetVertexBuffer(vBuffer);

		m_vertexDataHead = new VertexData[MAX_VERTEX_COUNT];

		//Setup index buffer
		uint32_t* quadIndices = new uint32_t[MAX_INDEX_COUNT];
		uint32_t offset = 0;
		for (uint32_t i = 0; i < MAX_INDEX_COUNT; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}
		auto iBuffer = CreateRef<IndexBuffer>(quadIndices, MAX_QUADS_COUNT_FOR_CALL * 6);
		m_vertexArray->SetIndexBuffer(iBuffer);
		delete[] quadIndices;

		//Setup quad vertex positions
		m_quadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		m_quadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		m_quadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		m_quadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

		m_shader = CreateRef <Shader>("assets/shaders/FlatColorShader.glsl");
	}

	Sandbox::~Sandbox()
	{

	}

	void Sandbox::UpdateInternal()
	{
		if (m_frameBuffer) m_frameBuffer->Bind();

		glClearColor(0.1f, 0.1f, 0.1f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (m_frameBuffer) m_frameBuffer->Unbind();

		m_vertexDataPtr = m_vertexDataHead;
		for (int i = 0; i < QUAD_VERTEX_COUNT; i++)
		{
			m_vertexDataPtr->Position = m_quadVertexPositions[i];
			m_vertexDataPtr->Color = glm::vec4(1.f, 0.f, 0.f, 1.f);
			m_vertexDataPtr++;
		}

		// m_SpritesCount++;
		// m_IndexCount += 6;

		uint32_t dataSize = (uint32_t)((uint8_t*)m_vertexDataPtr - (uint8_t*)m_vertexDataHead);
		m_vertexArray->GetVertexBuffer()->SetData(m_vertexDataHead, dataSize);
		m_vertexArray->Bind();
		m_shader->Bind();
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);
		
		// Clear();
	}
}
