#pragma once

#include <Fjord.h>

namespace Fjord
{
	class Sandbox : public Application
	{
	public:
		Sandbox();
		~Sandbox();

	protected:
		void UpdateInternal() override;

	private:
		Ref<Scene> m_scene;

		//TEMP??
		Ref<RenderSystem> m_renderSys;

	private:
		const uint32_t QUAD_VERTEX_COUNT = 4;
		const uint32_t QUAD_INDEX_COUNT = 6;
		const uint32_t MAX_QUADS_COUNT_FOR_CALL = 1000; //max amout of quads that could be drawn per one draw call
		const uint32_t MAX_VERTEX_COUNT = QUAD_VERTEX_COUNT * MAX_QUADS_COUNT_FOR_CALL;
		const uint32_t MAX_INDEX_COUNT = QUAD_INDEX_COUNT * MAX_QUADS_COUNT_FOR_CALL;

		struct VertexData
		{
			glm::vec3 Position;
			glm::vec4 Color;
		};

	private:
		Ref<VertexArray> m_vertexArray;
		Ref<Shader> m_shader;

		VertexData* m_vertexDataHead{nullptr};
		VertexData* m_vertexDataPtr{nullptr};

		glm::vec4 m_quadVertexPositions[4];

		Ref<Framebuffer> m_frameBuffer;

	};
}