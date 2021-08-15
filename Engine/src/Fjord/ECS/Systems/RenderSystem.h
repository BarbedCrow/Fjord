#pragma once

#include <glm/gtc/type_ptr.hpp>

#include "Fjord/ECS/Systems/GameSystem.h"
#include "Fjord/ECS/Components/Components.h"

#include "Fjord/Render/Framebuffer.h"

#include "Fjord/ECS/Scene.h"

namespace Fjord
{
	//SPRITES BUFFER/////////////////////////////////////////////////////
	struct SpriteVertexData
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TextureCoord;
		float TextureSlot;
		float TilingFactor;
	};

	struct SpritesBuffer
	{
		const uint32_t QUAD_VERTEX_COUNT = 4;
		const uint32_t QUAD_INDEX_COUNT = 6;
		const uint32_t MAX_QUADS_COUNT_FOR_CALL = 1; //max amout of quads that could be drawn per one draw call
		const uint32_t MAX_VERTEX_COUNT = QUAD_VERTEX_COUNT * MAX_QUADS_COUNT_FOR_CALL;
		const uint32_t MAX_INDEX_COUNT = QUAD_INDEX_COUNT * MAX_QUADS_COUNT_FOR_CALL;

		glm::vec4 m_QuadVertexPositions[4];

		int m_MaxTextureCount; // max amount of images that can be bound at once

		SpriteVertexData* m_VertexDataHead = nullptr;
		SpriteVertexData* m_VertexDataPtr = nullptr;

		uint32_t m_IndexCount = 0;
		uint32_t m_SpritesCount = 0;

		Ref<VertexArray> m_VertexArray;
		Ref<Shader> m_Shader;

		std::unordered_map<std::string, Ref<Texture2D>*> m_BindedTextures;
		uint32_t m_BindedTexturesCount = 0;

		void Init();
		void Clear();
	};
	////////////////////////////////////////////////////////////////////


	//RENDER SYSTEM////////////////////////////////////////////////////
	class RenderSystem : public GameSystem
	{
	public:
		RenderSystem(Ref<Scene>& scene);
		virtual ~RenderSystem() override {}

		void SetFramebuffer(Ref<Framebuffer> frameBuffer) { m_FrameBuffer = frameBuffer; }

		bool HandleOnWindowResize(uint32_t width, uint32_t height);

		virtual void Activate() override;
		virtual void Update() override;
	private:
		void RenderSprites();
		void FlushSprites();
		void SubmitSpriteForRender(TransformComponent& tc, SpriteRendererComponent& sc, CameraComponent& camera);
	private:
		
		Ref<Framebuffer> m_FrameBuffer;
		SpritesBuffer m_SpritesBuffer;
		TextureLibrary m_TextureLibrary;
	};
	////////////////////////////////////////////////////////////////////
}

