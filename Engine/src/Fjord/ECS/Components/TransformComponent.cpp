#include "fjordpch.h"
#include "TransformComponent.h"

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