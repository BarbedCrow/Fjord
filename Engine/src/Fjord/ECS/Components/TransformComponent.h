#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "Component.h"

namespace Fjord
{
	class TransformComponent : public Component

	{
	public:
		TransformComponent(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale);
		TransformComponent(const glm::vec3& pos, const glm::vec3& rot)
			: TransformComponent(pos, rot, glm::vec3(1.f))
		{}
		TransformComponent(const glm::vec3& pos)
			: TransformComponent(pos, glm::vec3(0.f), glm::vec3(1.f))
		{}
		TransformComponent()
			: TransformComponent(glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f))
		{}
		TransformComponent(const TransformComponent& obj);

		//GETTERS
		const glm::mat4& ViewTransform() const { return m_tr; }
		const glm::vec3& ViewPos() const { return m_pos; }
		const glm::vec3& ViewRot() const { return m_rot; }
		const glm::vec3& ViewScale() const { return m_scale; }

		glm::vec3 GetPos() const { return m_pos; }
		glm::vec3 GetRot() const { return m_rot; }
		glm::vec3 GetScale() const { return m_scale; }

		//SETTERS
		void SetPos(const glm::vec3& pos);
		void SetRot(const glm::vec3& rot);
		void SetScale(const glm::vec3& scale);

	protected:
		virtual void SetupProxy() override;

	private:
		void CalculateTransform();

	private:
		glm::mat4 m_tr {};
		glm::vec3 m_pos { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_rot { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_scale { 1.0f, 1.0f, 1.0f };
	};
}
