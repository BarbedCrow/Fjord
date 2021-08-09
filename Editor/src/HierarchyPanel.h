#pragma once

#include <Fjord.h>

namespace Fjord
{
	class HierarchyPanel
	{
	public:
		HierarchyPanel();
		~HierarchyPanel() = default;

		void SetScene(const Ref<Scene>& scene) { m_Scene = scene; }

		const entt::entity& GetSelectedEntity() const { return m_SelectedEntt; }

		void Update();
	private:
		Ref<Scene> m_Scene;

		entt::entity m_SelectedEntt = entt::null;
		bool m_ItemWasRightClicked = false;

		bool m_RenameActive = false;
	};
}

