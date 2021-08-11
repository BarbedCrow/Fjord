#include "fjordpch.h"
#include "RenderComponent.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "Fjord/Utils/YAMLUtils.h"

namespace Fjord
{
	RenderComponent::RenderComponent()
	{
		SetupProxy();

		float vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		};

		auto vBuffer = CreateRef<VertexBuffer>(vertices, sizeof(vertices));
		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float2, "a_TexCoord"},
		};
		vBuffer->SetLayout(layout);

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
		auto iBuffer = CreateRef<IndexBuffer>(indices, 6);

		VerticesArray = CreateRef<VertexArray>();
		VerticesArray->AddVertexBuffer(vBuffer);
		VerticesArray->SetIndexBuffer(iBuffer);

		Material = CreateRef <Shader>("assets/shaders/FlatColorShader.glsl");
	}

	void RenderComponent::SetupProxy()
	{
		m_Proxy.Name = "Render";
		m_Proxy.Members.push_back(CreateRef<ComponentMemberColorRGBA>("Color", &Color));
	}

}