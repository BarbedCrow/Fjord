#pragma once

#include <Fjord.h>

namespace Fjord
{
	class HierarchyPanel
	{
	public:
		HierarchyPanel();
		~HierarchyPanel() = default;

		void SetScene(Ref<Scene> scene) { m_Scene = scene; }

		void Update();
	private:
		Ref<Scene> m_Scene;

		entt::entity m_SelectedEntt;

		bool m_RenameActive = false;
	};
}

