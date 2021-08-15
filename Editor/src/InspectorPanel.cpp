#include "InspectorPanel.h"

#include <iostream>

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

#define ENTT_STANDARD_CPP

namespace Fjord
{

	void InspectorPanel::Update(const entt::entity& entt)
	{
		ImGui::Begin("Inspector");
		auto registry = m_Scene->GetRegistry();
		if (registry->valid(entt))
		{
			const auto& id = registry->get<UIDComponent>(entt);
			ImGui::Text(id.UID.c_str());
			ImGui::Separator();
			
			//Display Components
			registry->visit(entt, [&](const auto info)
				{
					const auto type = entt::resolve(info);
					entt::meta_any any = type.func(Component::GET_FUNC).invoke({}, entt::forward_as_meta(*registry), entt);
					auto comp = any.try_cast<Component>();
					DisplayComponent(comp);
				});

			//Handle Context Menus
			if (ImGui::IsMouseClicked(ImGuiMouseButton_Right) && ImGui::IsWindowHovered())
			{
				ImGui::OpenPopup("Context");
			}

			if (ImGui::BeginPopup("Context"))
			{
				for (const auto& it : Component::GetMetaComponentsStorage())
				{
					if (ImGui::MenuItem(it.first.c_str()))
					{
						//TO DO: check if the entity already has this component
						auto compType = entt::resolve(it.second);
						auto compMeta = compType.func(Component::CREATE_FUNC).invoke({}, entt::forward_as_meta(*registry), entt);
					}
				}
				ImGui::EndPopup();
			}
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
			else if (auto castMember = std::dynamic_pointer_cast<ComponentMemberTexture>(member))
			{
				// TO DO: Support
			}
			else if (auto castMember = std::dynamic_pointer_cast<ComponentMemberFloat>(member))
			{
				ImGui::DragFloat(castMember->Name.c_str(), castMember->Value);
			}
		}
	}
}
