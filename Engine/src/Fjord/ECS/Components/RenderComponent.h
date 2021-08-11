#pragma once

#include "Component.h"
#include "Fjord/Render/Buffer.h"
#include "Fjord/Render/Shader.h"
#include "Fjord/Render/VertexArray.h"
#include "Fjord/Render/Texture.h"
#include "Fjord/Render/Camera.h"

namespace Fjord
{
	class RenderComponent : public Component
	{
	public:
		RenderComponent();
		RenderComponent(const RenderComponent&) = default;
	public:

		Ref<VertexArray> VerticesArray;
		Ref<Shader> Material; // replace with material
		Ref<Texture2D> Texture;
		glm::vec4 Color = {1.0f, 1.0f, 1.0f, 1.0f};
	protected:
		virtual void SetupProxy() override;
	};
}