#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Fjord/ECS/Systems/GameSystem.h"
#include "Fjord/ECS/Components/Components.h"

namespace Fjord
{
	class RenderSystem : public GameSystem
	{
	public:
		RenderSystem(entt::registry* registry) : GameSystem(registry) {}
		virtual ~RenderSystem() override {}

		virtual void Update() override;
	private:
		glm::vec4 testColor = glm::vec4(1.f);
	};
}

