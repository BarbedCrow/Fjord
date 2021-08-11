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
		CameraComponent() = default;
		CameraComponent(float aspectRatio)
			:
			AspectRatio(aspectRatio),
			Camera(CreateRef<OrthographicCamera>(-AspectRatio * ZoomLevel, AspectRatio * ZoomLevel, -ZoomLevel, ZoomLevel))
		{}

	public:
		Ref<OrthographicCamera> Camera;

		float Speed = 1.0f;
		float ZoomSpeed = 0.25f;
		float ZoomLevel = 1.0f;

		float AspectRatio;
	protected:
		virtual void SetupProxy() override {}
	};
}

