#include "fjordpch.h"

#include "PlayerMovementSystem.h"

#include "Fjord/ECS/Components/Components.h"
#include "Fjord/core/Input.h"
#include "Fjord/core/Time.h"

namespace Fjord
{
	// TEMP VALUE. Move it to some character's settings
	const float SPEED = 1.f;
	const float ROTATION_SPEED = 10.0f;

	void PlayerMovementSystem::Update()
	{
		auto registry = m_scene->GetRegistry();
		float dt = Time::GetDeltaTime();
		for (auto&& [entt, tr, camera] :
			registry->view<TransformComponent, PerspectiveCameraComponent>()
				.each()) {
			tr.SetPos(tr.GetPos() + GetDesiredVelocity() * dt);

			auto newRot = GetDesiredRotation();
			if (newRot != glm::vec3(0.f)) {
				camera.Rotate(tr.GetPos(), newRot * dt);
			}
		}
	}

	glm::vec3& PlayerMovementSystem::GetDesiredVelocity()
	{
		glm::vec3 velocity { 0.f };
		if (Input::IsKeyPressed(FJORD_KEY_W)) {
			velocity.z += SPEED;
		}
		else if (Input::IsKeyPressed(FJORD_KEY_S)) {
			velocity.z -= SPEED;
		}
		else if (Input::IsKeyPressed(FJORD_KEY_A)) {
			velocity.x += SPEED;
		}
		else if (Input::IsKeyPressed(FJORD_KEY_D)) {
			velocity.x -= SPEED;
		}
		else if (Input::IsKeyPressed(FJORD_KEY_Q)) {
			velocity.y += SPEED;
		}
		else if (Input::IsKeyPressed(FJORD_KEY_E)) {
			velocity.y -= SPEED;
		}

		return velocity;
	}

	glm::vec3& PlayerMovementSystem::GetDesiredRotation()
	{
		glm::vec3 rotation { 0.f };

		if (Input::IsKeyPressed(FJORD_KEY_UP)) {
			rotation.x -= ROTATION_SPEED;
		}
		if (Input::IsKeyPressed(FJORD_KEY_DOWN)) {
			rotation.x += ROTATION_SPEED;
		}
		if (Input::IsKeyPressed(FJORD_KEY_LEFT)) {
			rotation.y -= ROTATION_SPEED;
		}
		if (Input::IsKeyPressed(FJORD_KEY_RIGHT)) {
			rotation.y += ROTATION_SPEED;
		}

		return rotation;
	}

} // namespace Fjord
