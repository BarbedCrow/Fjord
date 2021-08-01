#pragma once

#include <glm/glm.hpp>

namespace Fjord
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		void SetPosition(glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }
		void SetRotation(float zRotation) { m_Rotation = glm::radians(zRotation); RecalculateViewMatrix(); }

		const glm::vec3& GetPosition() const { return m_Position; }
		float GetRotation() const { return m_Rotation; }

		void SetProjectionMatrix(float left, float right, float bottom, float top);

		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		//TEMP SOLUTION. camera should refer to transform component
		glm::vec3 m_Position;
		float m_Rotation = 0.0f;
	};
}
