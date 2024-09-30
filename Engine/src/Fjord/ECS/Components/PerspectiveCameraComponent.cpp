#include "fjordpch.h"

#include "PerspectiveCameraComponent.h"

#include <Fjord/core/Application.h>

#include <glm/gtx/quaternion.hpp>

namespace Fjord
{
	PerspectiveCameraComponent::PerspectiveCameraComponent()
		: m_viewMatrix(1.f)
	{
		m_aspectRatio = Application::Get().GetWindow()->GetAspectRatio();
		SetFov(45.f);
		float nearPlane = 0.1f;
		float farPlane = 100.0f;
		m_projectionMatrix = glm::perspective(m_fov, m_aspectRatio, nearPlane, farPlane);
		m_vpMatrix = m_projectionMatrix * m_viewMatrix;
	}

	void PerspectiveCameraComponent::Rotate(glm::vec3 pos, glm::vec3 rot)
	{
		// glm::vec3 target(0.f, 0.f, 1.f);
		// glm::vec3 up(0.f, 1.f, 0.f);
		m_viewMatrix *= glm::toMat4(glm::quat(glm::radians(rot)));
		m_vpMatrix = m_projectionMatrix * m_viewMatrix;
	}

	void PerspectiveCameraComponent::SetupProxy()
	{
		m_proxy.Name = entt::resolve<PerspectiveCameraComponent>().info().name();
		m_proxy.Members.push_back(CreateRef<ComponentMemberFloat>("FOV", &m_fov));
	}

}
