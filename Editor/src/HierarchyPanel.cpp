#include "HierarchyPanel.h"

#include <imgui.h>

namespace Fjord
{

	HierarchyPanel::HierarchyPanel()
	{

	}

	void HierarchyPanel::Update()
	{
		FJORD_CORE_ASSERT(m_Scene);

		/*bool showDemo = true;
		ImGui::ShowDemoWindow(&showDemo);*/

		ImGuiTreeNodeFlags flags;
		
		ImGui::Begin("Hierarchy");
		auto view = m_Scene->GetRegistry()->view<UIDComponent>();
		for (auto entt : view)
		{
			flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_SpanFullWidth; //TEMP. Rework after adding parents and children for entities
			if (m_SelectedEntt == entt) flags |= ImGuiTreeNodeFlags_Selected;

			auto& uid = view.get<UIDComponent>(entt);
			ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entt, flags, uid.UID.c_str());

			if (ImGui::IsItemClicked())
			{
				m_SelectedEntt = entt;
			}

			if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
			{
				m_SelectedEntt = entt;
				ImGui::OpenPopup("test");
			}
		}

		//context menu for items
		if (ImGui::BeginPopup("test"))
		{
			if (ImGui::MenuItem("Rename"))
			{
				m_RenameActive = true;
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		//rename feature
		if (m_RenameActive)
		{
			auto& uid = view.get<UIDComponent>(m_SelectedEntt);
			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			std::strncpy(buffer, uid.UID.c_str(), sizeof(buffer));
			if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
			{
				uid.UID = std::string(buffer);
			}
			if (ImGui::IsItemDeactivatedAfterEdit())
			{
				m_RenameActive = false;
			}
		}

		ImGui::End();
	}

}