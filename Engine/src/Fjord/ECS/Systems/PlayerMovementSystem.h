#pragma once

#include "GameSystem.h"

#include "glm/glm.hpp"

namespace Fjord
{
	class PlayerMovementSystem : public GameSystem
	{
	public:
		PlayerMovementSystem(Ref<Scene>& scene) : GameSystem(scene) {}
		virtual ~PlayerMovementSystem() override {}

		virtual void Activate() override;
		virtual void Deactivate() override;

		virtual void Update() override;
	private:
		/*returns velocity based on player's inputs*/
		glm::vec3& GetDesiredVelocity();
	};
}
