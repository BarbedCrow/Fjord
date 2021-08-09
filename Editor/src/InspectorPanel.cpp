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

			registry->visit(entt, [&](const auto info)
				{
					const auto type = entt::resolve(info);
					auto any = type.func(Component::GET_FUNC).invoke({}, entt::forward_as_meta(*registry), entt);
					type.func(Component::EDITOR_DISPLAY_FUNC).invoke(any);
				});
		}

		ImGui::End();
	}
}
