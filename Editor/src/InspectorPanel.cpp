#include "InspectorPanel.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

namespace Fjord
{
	InspectorPanel::InspectorPanel()
	{

	}

	void InspectorPanel::Update(const entt::entity& entt)
	{
		ImGui::Begin("Inspector");
		if (entt != entt::null)
		{
			auto registry = m_Scene->GetRegistry();
			const auto& id = registry->get<UIDComponent>(entt);
			ImGui::Text(id.UID.c_str());
			ImGui::Separator();
			
			/*const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed 
				| ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;*/

			const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanFullWidth;
			auto tc = registry->try_get<TransformComponent>(entt);
			if (tc != nullptr)
			{
				if (ImGui::CollapsingHeader("Transform", treeNodeFlags))
				{
					ImGui::DragFloat3("Translation", glm::value_ptr(tc->Translation), 0.1f, 0.0f, 100.0f);
					ImGui::DragFloat3("Rotation", glm::value_ptr(tc->Rotation), 0.1f, 0.0f, 100.0f);
					ImGui::DragFloat3("Scale", glm::value_ptr(tc->Scale), 0.1f, 0.0f, 100.0f);
				}
;			}
			
			auto rc = registry->try_get<RenderComponent>(entt);
			if (rc != nullptr)
			{
				if (ImGui::CollapsingHeader("Render", treeNodeFlags))
				{
					ImGui::ColorEdit4("Color", glm::value_ptr(rc->Color));
				}
			}
		}

		ImGui::End();
	}
}
