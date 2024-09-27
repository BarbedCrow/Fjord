#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Fjord/ECS/Components/Component.h"

namespace Fjord
{
	class PerspectiveCameraComponent : public Component
	{
	public:
		PerspectiveCameraComponent();

		const glm::mat4& GetViewMatrix() const { return m_viewMatrix; }
		const glm::mat4& GetProjectionMatrix() const { return m_projectionMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_vpMatrix; }

		// returns FOV value in degrees
		float GetFov(){ return glm::degrees(m_fov); }
		void SetFov(float deg) { m_fov = glm::radians(deg); }

	protected:
		void SetupProxy() override;

	private:
		float m_aspectRatio{0.f};
		float m_fov{0.f};

		glm::mat4 m_viewMatrix{};
		glm::mat4 m_projectionMatrix{};
		glm::mat4 m_vpMatrix{};
	};
}

