#pragma once

#include <Fjord.h>

#include <Fjord/ECS/Components/ModelRendererComponent.h>

namespace Fjord
{
	class RenderSystem : public GameSystem
	{
	public:
		RenderSystem(Ref<Scene>& scene);
		~RenderSystem() override {}

		void SetFramebuffer(Ref<Framebuffer> frameBuffer)
		{
			m_frameBuffer = frameBuffer;
		}

		void Activate() override;
		void Update() override;

	private:
		void Init();

		void Render();
		void RenderObj(const TransformComponent& tr, ModelRendererComponent& rc);
		void Flush();

	private:
		const uint32_t MAX_VERTEX_COUNT = 16777216;

		struct VertexData
		{
			glm::vec3 Position;
			glm::vec2 UvCoord;
		};

	private:
		Ref<VertexArray> m_vertexArray;
		Ref<Shader> m_shader;

		VertexData* m_vertexDataHead { nullptr };
		VertexData* m_vertexDataPtr { nullptr };

		glm::vec4 m_quadVertexPositions[4];

		Ref<Framebuffer> m_frameBuffer;
	};
}
