#pragma once

#include "GameSystem.h"

#include "Fjord/ECS/Scene.h"

namespace Fjord
{
	class EditorCameraControllerSystem : public GameSystem
	{
	public:
		EditorCameraControllerSystem(Ref<Scene>& scene) : GameSystem(scene) {}
		virtual ~EditorCameraControllerSystem() override {}

		virtual void Activate() override;
		virtual void Deactivate() override;

		virtual void Update() override;
	private:
		bool HandleOnMouseScrolled(float x, float y);
	};

}
