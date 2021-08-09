#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Fjord/Render/Camera.h"
#include "Fjord/ECS/Components/Component.h"

namespace Fjord
{
	class CameraComponent : public Component
	{
	public:
		CameraComponent() : Component() {}
		CameraComponent(float aspectRatio)
			:
			AspectRatio(aspectRatio),
			Camera(CreateRef<OrthographicCamera>(-AspectRatio * ZoomLevel, AspectRatio * ZoomLevel, -ZoomLevel, ZoomLevel))
		{}

		virtual void Load(YAML::Node& entt) override;
		virtual void Save(YAML::Emitter& out) override;
		virtual void EditorDisplay() override {}
	public:
		Ref<OrthographicCamera> Camera;

		float Speed = 1.0f;
		float ZoomSpeed = 0.25f;
		float ZoomLevel = 1.0f;

		float AspectRatio;
	};
}

