#include "fjordpch.h"
#include "RenderSystem.h"

#include <glad/glad.h>
#include <imgui.h>

#include "Fjord/core/Application.h"
#include "Fjord/core/Time.h"

namespace Fjord
{
	//RENDER SATS////////////////////////////////////////////
	struct RenderStats
	{
		float RenderTime = 0;
		int DrawCalls = 0;
		int EntitiesCount = 0;
	};

	static RenderStats s_RenderStats;

	static void DisplayProfileInfo()
	{
		ImGui::Begin("Render Stats");

		float timeMs = s_RenderStats.RenderTime * 1000.f;
		int fps = 1000 / timeMs;

		ImGui::Text("Render time: %.2fms", timeMs);
		ImGui::Text("FPS: %i", fps);
		ImGui::Text("Draw Calls: %i", s_RenderStats.DrawCalls);
		ImGui::Text("Entities Count: %i", s_RenderStats.EntitiesCount);

		ImGui::End();
	}
	////////////////////////////////////////////////////////


	//SPRITES BUFFER///////////////////////////////////////
	void SpritesBuffer::Init()
	{
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &m_MaxTextureCount);

		m_VertexArray = CreateRef<VertexArray>();

		//Setup vertex buffer
		auto vBuffer = CreateRef<VertexBuffer>(MAX_VERTEX_COUNT * sizeof(SpriteVertexData));
		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"},
			{ShaderDataType::Float2, "a_TexCoord"},
			{ ShaderDataType::Float,  "a_TexIndex"},
			{ ShaderDataType::Float,  "a_TilingFactor"},
		};
		vBuffer->SetLayout(layout);
		m_VertexArray->SetVertexBuffer(vBuffer);

		m_VertexDataHead = new SpriteVertexData[MAX_VERTEX_COUNT];

		//Setup index buffer
		uint32_t* quadIndices = new uint32_t[MAX_INDEX_COUNT];
		uint32_t offset = 0;
		for (uint32_t i = 0; i < MAX_INDEX_COUNT; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}
		auto iBuffer = CreateRef<IndexBuffer>(quadIndices, MAX_QUADS_COUNT_FOR_CALL * 6);
		m_VertexArray->SetIndexBuffer(iBuffer);
		delete[] quadIndices;

		//Setup quad vertex positions
		m_QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		m_QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		m_QuadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		m_QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

		m_Shader = CreateRef <Shader>("assets/shaders/BasicShader.glsl");
	}

	void SpritesBuffer::Clear()
	{
		for (auto& it : m_BindedTextures)
		{
			it.second->get()->Unbind();
		}
		m_BindedTextures.clear();

		m_BindedTexturesCount = 0;
		m_VertexDataPtr = m_VertexDataHead;
		m_IndexCount = 0;
		m_SpritesCount = 0;
	}
	//////////////////////////////////////////////////////


	//RENDER SYSTEM//////////////////////////////////////

	static bool Compare(const std::pair<TransformComponent&, SpriteRendererComponent&>& first, const std::pair<TransformComponent&, SpriteRendererComponent&>& second)
	{
		return first.first.Translation.z < second.first.Translation.z;
	}

	RenderSystem::RenderSystem(Ref<Scene>& scene) : GameSystem(scene)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_SpritesBuffer.Init();
	}

	void RenderSystem::Activate()
	{
		GameSystem::Activate();

		Application::Get().GetWindow()->OnWindowResize->AddListener(BIND_EVENT_HANDLER_2(RenderSystem::HandleOnWindowResize));
	}

	void RenderSystem::Update()
	{
		//stats
		s_RenderStats.DrawCalls = 0;
		s_RenderStats.EntitiesCount = 0;

		//setup
		if (m_FrameBuffer) m_FrameBuffer->Bind();

		glClearColor(0.1f, 0.1f, 0.1f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//render
		float begTime = Time::GetTime();
		RenderSprites();
		s_RenderStats.RenderTime = Time::GetTime() - begTime;

		if (m_FrameBuffer) m_FrameBuffer->Unbind();

		DisplayProfileInfo();
	}

	void RenderSystem::RenderSprites()
	{
		auto registry = m_Scene->GetRegistry();
		auto camView = registry->view<CameraComponent>();
		CameraComponent& camera = camView.get<CameraComponent>(camView[0]);

		//Sort sprites in Z-order
		std::list<std::pair<TransformComponent&, SpriteRendererComponent&>> sprites;
		for (auto&& [entity, tr, render] : registry->view<TransformComponent, SpriteRendererComponent>().each())
		{
			sprites.push_back(std::pair<TransformComponent&, SpriteRendererComponent&>(tr, render));
		}
		sprites.sort(Compare);

		//Submit sprites
		m_SpritesBuffer.Clear();
		for (auto& it : sprites)
		{
			SubmitSpriteForRender(it.first, it.second, camera);
			if (m_SpritesBuffer.m_SpritesCount >= m_SpritesBuffer.MAX_QUADS_COUNT_FOR_CALL || m_SpritesBuffer.m_BindedTexturesCount >= m_SpritesBuffer.m_MaxTextureCount) FlushSprites();
		}

		if (m_SpritesBuffer.m_SpritesCount > 0) FlushSprites();
	}

	void RenderSystem::FlushSprites()
	{
		s_RenderStats.DrawCalls++;

		uint32_t dataSize = (uint32_t)((uint8_t*)m_SpritesBuffer.m_VertexDataPtr - (uint8_t*)m_SpritesBuffer.m_VertexDataHead);
		m_SpritesBuffer.m_VertexArray->GetVertexBuffer()->SetData(m_SpritesBuffer.m_VertexDataHead, dataSize);
		m_SpritesBuffer.m_VertexArray->Bind();
		m_SpritesBuffer.m_Shader->Bind();
		glDrawElements(GL_TRIANGLES, m_SpritesBuffer.m_IndexCount, GL_UNSIGNED_INT, nullptr);
		
		m_SpritesBuffer.Clear();
	}

	void RenderSystem::SubmitSpriteForRender(TransformComponent& tc, SpriteRendererComponent& sc, CameraComponent& camera)
	{
		if (m_SpritesBuffer.m_BindedTextures.find(sc.Texture) == m_SpritesBuffer.m_BindedTextures.end())
		{
			auto& texture = m_TextureLibrary.Get(sc.Texture);
			m_SpritesBuffer.m_BindedTextures[sc.Texture] = &texture;
			texture->Bind(m_SpritesBuffer.m_BindedTexturesCount++);
		}

		//TO DO: add culling
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		auto quadTr = camera.Camera->GetViewProjectionMatrix() * tc.GetTransform();
		for (int i = 0; i < m_SpritesBuffer.QUAD_VERTEX_COUNT; i++)
		{
			m_SpritesBuffer.m_VertexDataPtr->Position = quadTr * m_SpritesBuffer.m_QuadVertexPositions[i];
			m_SpritesBuffer.m_VertexDataPtr->Color = sc.Color;
			m_SpritesBuffer.m_VertexDataPtr->TextureCoord = textureCoords[i];
			m_SpritesBuffer.m_VertexDataPtr->TextureSlot = m_SpritesBuffer.m_BindedTextures.find(sc.Texture)->second->get()->GetSlot();
			m_SpritesBuffer.m_VertexDataPtr->TilingFactor = sc.TilingFactor;
			m_SpritesBuffer.m_VertexDataPtr++;
		}

		m_SpritesBuffer.m_SpritesCount++;
		m_SpritesBuffer.m_IndexCount += 6;
		
		s_RenderStats.EntitiesCount++;
	}

	bool RenderSystem::HandleOnWindowResize(uint32_t width, uint32_t height)
	{
		auto registry = m_Scene->GetRegistry();
		auto camView = registry->view<CameraComponent>();
		CameraComponent& camera = camView.get<CameraComponent>(camView[0]);

		camera.AspectRatio = (float)width / (float)height;
		camera.Camera->SetProjectionMatrix(-camera.AspectRatio * camera.ZoomLevel, camera.AspectRatio * camera.ZoomLevel, -camera.ZoomLevel, camera.ZoomLevel);

		glViewport(0, 0, width, height);
		return true;
	}
	//////////////////////////////////////////////////////
}