#include "fjordpch.h"
#include "RenderSystem.h"

#include <glad/glad.h>
#include <imgui.h>

#include "Fjord/core/Application.h"

namespace Fjord
{
	void RenderSystem::Activate()
	{
		GameSystem::Activate();

		Application::Get().GetWindow()->OnWindowResize->AddListener(BIND_EVENT_HANDLER_2(RenderSystem::HandleOnWindowResize));
	}

	void RenderSystem::Update()
	{
		auto registry = m_Scene->GetRegistry();
		if (m_FrameBuffer) m_FrameBuffer->Bind();

		glClearColor(0.1f, 0.1f, 0.1f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/*ImGui::Begin("TEST");
		ImGui::ColorPicker4("Color", glm::value_ptr(testColor));
		ImGui::End();*/

		auto camView = registry->view<CameraComponent>();
		auto camera = camView.get<CameraComponent>(camView[0]);

		for (auto&& [entity, tr, render] : registry->view<TransformComponent, RenderComponent>().each())
		{
			render.VerticesArray->Bind();
			render.shader->Bind();
			if (render.texture)
			{
				render.texture->Bind();
				render.shader->UploadUniformInt("u_Texture", 0);

			}
			render.shader->UploadUniformVec4("u_Color", render.Color);
			render.shader->UploadUniformMat4("u_ViewProjection", camera.Camera->GetViewProjectionMatrix());
			render.shader->UploadUniformMat4("u_Transform", tr.GetTransform());

			glDrawElements(GL_TRIANGLES, render.VerticesArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		}

		if (m_FrameBuffer) m_FrameBuffer->Unbind();
	}

	bool RenderSystem::HandleOnWindowResize(uint32_t width, uint32_t height)
	{
		auto registry = m_Scene->GetRegistry();
		auto camView = registry->view<CameraComponent>();
		auto camera = camView.get<CameraComponent>(camView[0]);

		camera.AspectRatio = (float)width / (float)height;
		camera.Camera->SetProjectionMatrix(-camera.AspectRatio * camera.ZoomLevel, camera.AspectRatio * camera.ZoomLevel, -camera.ZoomLevel, camera.ZoomLevel);

		glViewport(0, 0, width, height);
		return true;
	}
}