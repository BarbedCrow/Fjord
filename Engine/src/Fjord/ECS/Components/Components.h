#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "Fjord/Render/Buffer.h"
#include "Fjord/Render/Shader.h"
#include "Fjord/Render/VertexArray.h"

namespace Fjord
{
	struct TransformComponent
	{
		glm::vec3 Translation = { 0.0f, 0.0f ,0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f ,0.0f };
		glm::vec3 Scale = { 0.0f, 0.0f ,0.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& translation) : Translation(translation) {}

		glm::mat4 GetTransform() const
		{
			glm::mat4 rotation = glm::toMat4((glm::quat(Rotation)));
			return glm::mat4(
				glm::translate(glm::mat4(1.0f), Translation) *
				rotation *
				glm::scale(glm::mat4(1.0f), Scale)
			);
		}
	};

	struct RenderComponent
	{
		Ref<VertexArray> VerticesArray;
		Ref<Shader> shader; // replace with material

		RenderComponent() = default;
		RenderComponent(Ref<VertexArray> vArray, Ref<Shader> shader) 
			:
			VerticesArray(vArray),
			shader(shader)
		{}
	};
}