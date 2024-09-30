#include "fjordpch.h"

#include "RenderSystem.h"

#include <Fjord/ECS/Components/ModelRendererComponent.h>
#include <Fjord/ECS/Components/PerspectiveCameraComponent.h>

#include <glad/glad.h>
#include <imgui.h>

namespace Fjord
{
	RenderSystem::RenderSystem(Ref<Scene>& scene)
		: GameSystem(scene)
	{
		Init();
	}

	void RenderSystem::Activate() {}

	void RenderSystem::Init()
	{
		glEnable(GL_DEPTH_TEST);

		m_vertexArray = CreateRef<VertexArray>();

		m_shader = CreateRef<Shader>("resources/shaders/BasicModelShader.glsl");

		//VERTEX BUFFER
		auto vBuffer = CreateRef<VertexBuffer>(MAX_VERTEX_COUNT * sizeof(VertexData));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_UvCoord" },
		};
		vBuffer->SetLayout(layout);

		m_vertexArray->SetVertexBuffer(vBuffer);
	}

	void RenderSystem::Update()
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Render();
	}

	void RenderSystem::Render()
	{
		auto registry = m_scene->GetRegistry();

		for (auto&& [entity, tr, rc] :
			registry->view<TransformComponent, ModelRendererComponent>().each()) {
			RenderObj(tr, rc);
		}
	}

	void RenderSystem::RenderObj(const TransformComponent& tr, ModelRendererComponent& rc)
	{
		auto registry = m_scene->GetRegistry();
		TransformComponent cameraTr;
		PerspectiveCameraComponent camera;
		for (auto&& [entity, tr, cam] :
			registry->view<TransformComponent, PerspectiveCameraComponent>().each()) {
			cameraTr = tr;
			camera = cam;
		}

		auto mvpMatrix = camera.GetViewProjectionMatrix() * cameraTr.ViewTransform() * tr.ViewTransform();
		m_shader->UploadUniformMat4("uMVPMatrix", mvpMatrix);

		rc.Bind();

		auto iBuffer = CreateRef<IndexBuffer>(rc.GetIndices().data(), rc.GetIndices().size());
		m_vertexArray->SetIndexBuffer(iBuffer);

		std::vector<VertexData> vertexData;
		for (auto idx = 0; idx < rc.GetVertices().size(); ++idx) {
			vertexData.push_back({ rc.GetVertices()[idx], rc.GetUvs()[idx] });
		}

		m_vertexArray->GetVertexBuffer()->SetData(vertexData.data(), sizeof(VertexData) * vertexData.size());
		m_vertexArray->Bind();
		m_shader->Bind();

		glDrawElements(GL_TRIANGLES, rc.GetIndices().size(), GL_UNSIGNED_INT, nullptr);

		rc.Unbind();
	}

	void RenderSystem::Flush()
	{
	}

} // namespace Fjord
