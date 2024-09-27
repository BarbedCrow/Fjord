#include "fjordpch.h"
#include "TransformComponent.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "Fjord/Utils/YAMLUtils.h"

namespace Fjord
{
	TransformComponent::TransformComponent(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale)
	: m_pos(pos)
	, m_rot(rot)
	, m_scale(scale)
	{
		CalculateTransform();
	}

	TransformComponent::TransformComponent(const TransformComponent& obj)
	{
		m_pos = obj.m_pos;
		m_rot = obj.m_rot;
		m_scale = obj.m_scale;
		m_tr = obj.m_tr;
	}

	void TransformComponent::CalculateTransform()
	{
		m_tr = glm::mat4(
			glm::translate(glm::mat4(1.0f), m_pos) *
			glm::toMat4((glm::quat(glm::radians(m_rot)))) *
			glm::scale(glm::mat4(1.0f), m_scale)
		);
	}

	void TransformComponent::SetPos(const glm::vec3& pos)
	{
		m_pos = pos;
		CalculateTransform();
	}

	void TransformComponent::SetRot(const glm::vec3& scale)
	{
		m_scale = scale;
		CalculateTransform();
	}

	void TransformComponent::SetScale(const glm::vec3& rot)
	{
		m_rot = rot;
	}

	void TransformComponent::SetupProxy()
	{
		m_proxy.Name = entt::resolve<TransformComponent>().info().name();
		m_proxy.Members.push_back(CreateRef<ComponentMemberVec3>("Translation", &m_pos));
		m_proxy.Members.push_back(CreateRef<ComponentMemberVec3>("Rotation", &m_rot, -360.f, 360.f, 0.5));
		m_proxy.Members.push_back(CreateRef<ComponentMemberVec3>("Scale", &m_scale, 0.f));
	}

}