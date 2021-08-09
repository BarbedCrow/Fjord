#include "fjordpch.h"
#include "RenderComponent.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "Fjord/Utils/YAMLUtils.h"

namespace Fjord
{
	void RenderComponent::Load(YAML::Node& entt)
	{
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
		auto colorEnt = entt["Color"];
		Color = colorEnt ? colorEnt.as<glm::vec4>() : Color;
	}

	void RenderComponent::Save(YAML::Emitter& out)
	{
		out << YAML::Key << "Color" << YAML::Value << Color;
	}

	void RenderComponent::EditorDisplay()
	{
		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanFullWidth;
		if (ImGui::CollapsingHeader("Render", treeNodeFlags))
		{
			ImGui::ColorEdit4("Color", glm::value_ptr(Color));
		}
	}

}