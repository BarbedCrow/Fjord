#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Fjord/ECS/Systems/GameSystem.h"
#include "Fjord/ECS/Components/Components.h"

#include "Fjord/Render/Framebuffer.h"

#include "Fjord/ECS/Scene.h"

namespace Fjord
{
	class RenderSystem : public GameSystem
	{
	public:
		RenderSystem(Ref<Scene>& scene) : GameSystem(scene) {}
		virtual ~RenderSystem() override {}

		void SetActiveCamera(CameraComponent& camera) { m_Camera = camera; }
		void SetFramebuffer(Ref<Framebuffer> frameBuffer) { m_FrameBuffer = frameBuffer; }

		bool HandleOnWindowResize(uint32_t width, uint32_t height);

		virtual void Activate() override;
		virtual void Update() override;
	private:
		CameraComponent m_Camera;
		Ref<Framebuffer> m_FrameBuffer;
		glm::vec4 testColor = glm::vec4(1.f);
	};
}

