#include "fjordpch.h"

#include "PlayerMovementSystem.h"

#include "Fjord/core/Time.h"
#include "Fjord/ECS/Components/Components.h"
#include "Fjord/core/Input.h"

namespace Fjord
{
	//TEMP VALUE. Move it to some character's settings
	const float SPEED = 1.f;

	void PlayerMovementSystem::Update()
	{
		auto registry = m_scene->GetRegistry();
		float dt = Time::GetDeltaTime();
		for (auto&& [entt, tr, camera] : registry->view<TransformComponent, PerspectiveCameraComponent>().each())
		{
			tr.SetPos(tr.GetPos() + GetDesiredVelocity() * dt);
		}
	}

	glm::vec3& PlayerMovementSystem::GetDesiredVelocity()
	{
		glm::vec3 velocity{0.f};
		if (Input::IsKeyPressed(FJORD_KEY_W))
		{
			velocity.y += SPEED;
		}
		if (Input::IsKeyPressed(FJORD_KEY_S))
		{
			velocity.y -= SPEED;
		}
		if (Input::IsKeyPressed(FJORD_KEY_A))
		{
			velocity.x -= SPEED;
		}
		if (Input::IsKeyPressed(FJORD_KEY_D))
		{
			velocity.x += SPEED;
		}

		return velocity;
	}

}
