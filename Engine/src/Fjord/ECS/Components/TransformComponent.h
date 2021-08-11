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
		TransformComponent();
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& translation) : Translation(translation) {}

		glm::mat4 GetTransform() const;

		void* GetTranslation() { return &Translation; }
		
	public:
		glm::vec3 Translation = { 0.0f, 0.0f ,0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f ,0.0f }; //radians
		glm::vec3 Scale = { 1.0f, 1.0f ,1.0f };
	protected:
		virtual void SetupProxy() override;
	};
}