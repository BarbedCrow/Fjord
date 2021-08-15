#pragma once

#include "Component.h"
#include "Fjord/Render/Buffer.h"
#include "Fjord/Render/Shader.h"
#include "Fjord/Render/VertexArray.h"
#include "Fjord/Render/Texture.h"
#include "Fjord/Render/Camera.h"

namespace Fjord
{
	class SpriteRendererComponent : public Component
	{
	public:
		SpriteRendererComponent();
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
	public:

		Ref<Shader> Material; // replace with material
		std::string Texture = "assets\\textures\\quad.png";
		glm::vec4 Color = {1.0f, 1.0f, 1.0f, 1.0f};
		float TilingFactor = 1.f;
	protected:
		virtual void SetupProxy() override;
	};
}