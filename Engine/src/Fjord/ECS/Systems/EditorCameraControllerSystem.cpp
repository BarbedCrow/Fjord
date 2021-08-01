#include "fjordpch.h"
#include "EditorCameraControllerSystem.h"

#include "Fjord/core/Time.h"
#include "Fjord/ECS/Components/Components.h"
#include "Fjord/core/Input.h"

#include "Fjord/core/Application.h"

namespace Fjord
{
	void EditorCameraControllerSystem::Activate()
	{
		GameSystem::Activate();

		Application::Get().GetWindow()->OnMouseScrolled->AddListener(BIND_EVENT_HANDLER_2(EditorCameraControllerSystem::HandleOnMouseScrolled));
	}

	void EditorCameraControllerSystem::Deactivate()
	{
		GameSystem::Deactivate();
	}

	void EditorCameraControllerSystem::Update()
	{
		float dt = Time::GetDeltaTime();
		for (auto&& [entt, tr, camera] : m_Registry->view<TransformComponent, CameraComponent>().each())
		{
			if (Input::IsKeyPressed(FJORD_KEY_W))
			{
				camera.Camera->SetPosition(tr.Translation += glm::vec3(0, Time::GetDeltaTime() * camera.Speed, 0));
			}
			if (Input::IsKeyPressed(FJORD_KEY_S))
			{
				camera.Camera->SetPosition(tr.Translation -= glm::vec3(0, Time::GetDeltaTime() * camera.Speed, 0));
			}
			if (Input::IsKeyPressed(FJORD_KEY_A))
			{
				camera.Camera->SetPosition(tr.Translation -= glm::vec3(Time::GetDeltaTime() * camera.Speed, 0, 0));
			}
			if (Input::IsKeyPressed(FJORD_KEY_D))
			{
				camera.Camera->SetPosition(tr.Translation += glm::vec3(Time::GetDeltaTime() * camera.Speed, 0, 0));
			}
		}
	}
	bool EditorCameraControllerSystem::HandleOnMouseScrolled(float x, float y)
	{
		for (auto&& [entt, tr, camera] : m_Registry->view<TransformComponent, CameraComponent>().each())
		{
			camera.ZoomLevel -= y * camera.ZoomSpeed;
			camera.ZoomLevel = std::max(camera.ZoomLevel, 0.25f);
			camera.Camera->SetProjectionMatrix(-camera.AspectRatio * camera.ZoomLevel, camera.AspectRatio * camera.ZoomLevel, -camera.ZoomLevel, camera.ZoomLevel);
		}
		return true;
	}
}