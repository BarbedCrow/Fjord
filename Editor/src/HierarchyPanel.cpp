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
		m_ItemWasRightClicked = false;

		ImGuiTreeNodeFlags flags;
		
		ImGui::Begin("Hierarchy");
		auto registry = m_Scene->GetRegistry();
		auto view = registry->view<UIDComponent>(entt::exclude<EditorComponent>);
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
				m_ItemWasRightClicked = true;
				m_SelectedEntt = entt;
				ImGui::OpenPopup("Entity Context");
			}
		}

		if (ImGui::IsMouseClicked(ImGuiMouseButton_Right) && ImGui::IsWindowHovered() && !m_ItemWasRightClicked)
		{
			ImGui::OpenPopup("Context");
		}

		if (ImGui::BeginPopup("Context"))
		{
			if (ImGui::MenuItem("Add Entity"))
			{
				m_Scene->CreateEmptyEntity();
			}
			ImGui::EndPopup();
		}

		//context menu for items
		if (ImGui::BeginPopup("Entity Context"))
		{
			if (ImGui::MenuItem("Rename"))
			{
				m_RenameActive = true;
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::MenuItem("Delete"))
			{
				registry->destroy(m_SelectedEntt);
				m_SelectedEntt = entt::null;
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		//rename feature
		if (m_RenameActive)
		{
			ImGui::SetKeyboardFocusHere();
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