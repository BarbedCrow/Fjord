#include "Game.h"
#include <Fjord/ECS/SceneLoader.h>

namespace Fjord {
Game::Game() {
  m_scene = CreateRef<Scene>();
  // auto entt = m_scene->CreateEmptyEntity();
  // m_scene->CreateComponent<UIDComponent>(entt, "camera");
  // m_scene->CreateComponent<PerspectiveCameraComponent>(entt);
  // m_scene->CreateComponent<TransformComponent>(entt);

  SceneLoader(m_scene).Load("assets/scenes/test.fscene");
  SceneLoader(m_scene).Save("assets/scenes/test.fscene");
}

Game::~Game() {}

void Game::UpdateInternal() {}

} // namespace Fjord
