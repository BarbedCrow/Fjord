#pragma once

#include <Fjord.h>

namespace Fjord
{
	class InspectorPanel
	{
	public:
		InspectorPanel();
		~InspectorPanel() = default;

		void SetScene(Ref<Scene>& scene) { m_Scene = scene; }

		void Update(const entt::entity& entt);
	private:
		void DisplayComponent(Component* component);
	private:
		Ref<Scene> m_Scene;
	};
}

