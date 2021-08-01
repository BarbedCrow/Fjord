#include "fjordpch.h"
#include "RenderSystem.h"

#include <glad/glad.h>
#include <imgui.h>

namespace Fjord
{
	void RenderSystem::Update()
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui::Begin("TEST");
		ImGui::ColorPicker4("Color", glm::value_ptr(testColor));
		ImGui::End();

		for (auto&& [entity, tr, render] : m_Registry->view<TransformComponent, RenderComponent>().each())
		{
			render.VerticesArray->Bind();
			render.shader->Bind();
			render.shader->UploadUniformVec4("u_Color", testColor);
			glDrawElements(GL_TRIANGLES, render.VerticesArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		}
	}
}