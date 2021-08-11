#include "InspectorPanel.h"

#include <iostream>

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

#define ENTT_STANDARD_CPP

namespace Fjord
{
	InspectorPanel::InspectorPanel()
	{

	}

	void InspectorPanel::Update(const entt::entity& entt)
	{
		ImGui::Begin("Inspector");
		auto registry = m_Scene->GetRegistry();
		if (registry->valid(entt))
		{
			const auto& id = registry->get<UIDComponent>(entt);
			ImGui::Text(id.UID.c_str());
			ImGui::Separator();
			
			/*const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed 
				| ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;*/

			registry->visit(entt, [&](const auto info)
				{
					const auto type = entt::resolve(info);
					entt::meta_any any = type.func(Component::GET_FUNC).invoke({}, entt::forward_as_meta(*registry), entt);
					auto comp = any.try_cast<Component>();
					DisplayComponent(comp);
				});
		}

		ImGui::End();
	}

	void InspectorPanel::DisplayComponent(Component* component)
	{
		auto proxy = component->GetProxy();
		auto data = proxy.Members;
		if (data.size() == 0) return;
		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanFullWidth;
		if (!ImGui::CollapsingHeader(proxy.Name.c_str(), treeNodeFlags)) return;

		for (auto& member : data)
		{
			if (auto castMember = std::dynamic_pointer_cast<ComponentMemberVec3>(member))
			{
				ImGui::DragFloat3(castMember->Name.c_str(), glm::value_ptr(*castMember->Value), castMember->ChangeSpeed, castMember->MinVal, castMember->MaxVal);
			}
			else if (auto castMember = std::dynamic_pointer_cast<ComponentMemberColorRGBA>(member))
			{
				ImGui::ColorEdit4(castMember->Name.c_str(), glm::value_ptr(*castMember->Value));
			}
			else if (auto castMember = std::dynamic_pointer_cast<ComponentMemberString>(member))
			{
				char buffer[256];
				memset(buffer, 0, sizeof(buffer));
				std::strncpy(buffer, castMember->Value->c_str(), sizeof(buffer));
				if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
				{
					*castMember->Value = std::string(buffer);
				}
			}
		}
	}
}
