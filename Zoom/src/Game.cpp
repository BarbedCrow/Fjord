#include "Game.h"

#include <Fjord/ECS/Components/ModelRendererComponent.h>
#include "Fjord/ECS/Systems/PlayerMovementSystem.h"

#include <Fjord/ECS/SceneLoader.h>

namespace Fjord
{
	Game::Game()
	{
		m_scene = CreateRef<Scene>();
		auto entt = m_scene->CreateEmptyEntity();
		m_scene->CreateComponent<UIDComponent>(entt, "camera");
		m_scene->CreateComponent<TransformComponent>(entt, glm::vec3(0.f, 0.f, -4.5f));
		// m_scene->CreateComponent<TransformComponent>(entt);
		m_scene->CreateComponent<PerspectiveCameraComponent>(entt);

		entt = m_scene->CreateEmptyEntity();
		m_scene->CreateComponent<UIDComponent>(entt, "testObj");
		m_scene->CreateComponent<TransformComponent>(entt);
		m_scene->CreateComponent<ModelRendererComponent>(entt);

		// SceneLoader(m_scene).Load("assets/scenes/test.fscene");
		// SceneLoader(m_scene).Save("assets/scenes/test.fscene");

		m_systems.emplace_back(CreateRef<PlayerMovementSystem>(m_scene));
		m_systems.emplace_back(CreateRef<RenderSystem>(m_scene));
	}

	Game::~Game() {}

	void Game::UpdateInternal() {}

} // namespace Fjord
