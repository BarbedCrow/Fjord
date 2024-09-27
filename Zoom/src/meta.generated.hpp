#pragma once

#include "Fjord.h"

namespace Fjord
{
	void GenerateMetaData()
	{
		UIDComponent::Register<UIDComponent>();
		TransformComponent::Register<TransformComponent>();
		SpriteRendererComponent::Register<SpriteRendererComponent>();
		CameraComponent::Register<CameraComponent>();
		EditorComponent::Register<EditorComponent>();
		PerspectiveCameraComponent::Register<PerspectiveCameraComponent>();
	}
}
