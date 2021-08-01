#pragma once

#include "GameSystem.h"

namespace Fjord
{
	class EditorCameraControllerSystem : public GameSystem
	{
	public:
		EditorCameraControllerSystem(entt::registry* registry) : GameSystem(registry) {}
		virtual ~EditorCameraControllerSystem() override {}

		virtual void Activate() override;
		virtual void Deactivate() override;

		virtual void Update() override;
	private:
		bool HandleOnMouseScrolled(float x, float y);
	};

}
