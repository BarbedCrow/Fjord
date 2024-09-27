#include "fjordpch.h"
#include "PerspectiveCameraComponent.h"
#include <Fjord/core/Application.h>

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

	void PerspectiveCameraComponent::SetupProxy()
	{
		m_proxy.Name = entt::resolve<PerspectiveCameraComponent>().info().name();
		m_proxy.Members.push_back(CreateRef<ComponentMemberFloat>("FOV", &m_fov));
	}

}