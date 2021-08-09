#include "fjordpch.h"
#include "TransformComponent.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "Fjord/Utils/YAMLUtils.h"

namespace Fjord
{
	void TransformComponent::Load(YAML::Node& entt)
	{
		Translation = entt["Translation"].as<glm::vec3>();
		Rotation = entt["Rotation"].as<glm::vec3>();
		Scale = entt["Scale"].as<glm::vec3>();
	}

	void TransformComponent::Save(YAML::Emitter& out)
	{
		out << YAML::Key << "Translation" << YAML::Value << Translation;
		out << YAML::Key << "Rotation" << YAML::Value << Rotation;
		out << YAML::Key << "Scale" << YAML::Value << Scale;
	}

	void TransformComponent::EditorDisplay()
	{
		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanFullWidth;
		if (ImGui::CollapsingHeader("Transform", treeNodeFlags))
		{
			ImGui::DragFloat3("Translation", glm::value_ptr(Translation), 0.1f, 0.0f, 100.0f);
			ImGui::DragFloat3("Rotation", glm::value_ptr(Rotation), 0.1f, 0.0f, 100.0f);
			ImGui::DragFloat3("Scale", glm::value_ptr(Scale), 0.1f, 0.0f, 100.0f);
		}
	}

	glm::mat4 TransformComponent::GetTransform() const
	{
		glm::mat4 rotation = glm::toMat4((glm::quat(Rotation)));
		return glm::mat4(
			glm::translate(glm::mat4(1.0f), Translation) *
			rotation *
			glm::scale(glm::mat4(1.0f), Scale)
		);
	}

}