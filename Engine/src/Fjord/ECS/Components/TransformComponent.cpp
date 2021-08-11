#include "fjordpch.h"
#include "TransformComponent.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "Fjord/Utils/YAMLUtils.h"

namespace Fjord
{
	TransformComponent::TransformComponent()
	{
		SetupProxy();
	}

	glm::mat4 TransformComponent::GetTransform() const
	{
		glm::mat4 rotation = glm::toMat4((glm::quat(glm::radians(Rotation))));
		return glm::mat4(
			glm::translate(glm::mat4(1.0f), Translation) *
			rotation *
			glm::scale(glm::mat4(1.0f), Scale)
		);
	}

	void TransformComponent::SetupProxy()
	{
		m_Proxy.Name = "Transform";
		m_Proxy.Members.push_back(CreateRef<ComponentMemberVec3>("Translation", &Translation));
		m_Proxy.Members.push_back(CreateRef<ComponentMemberVec3>("Rotation", &Rotation, -360.f, 360.f, 0.5));
		m_Proxy.Members.push_back(CreateRef<ComponentMemberVec3>("Scale", &Scale, 0.f));
	}

}