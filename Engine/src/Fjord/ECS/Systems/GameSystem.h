#pragma once

#include <entt/entt.hpp>

#include "Fjord/ECS/Scene.h"

namespace Fjord
{
	class GameSystem
	{
	public:
		GameSystem(Ref<Scene>& scene, bool isActive = true) : m_Scene(scene), m_Active(isActive) {}
		virtual ~GameSystem() {}

		virtual void Activate() { m_Active = true; }
		virtual void Deactivate() { m_Active = false; }

		inline bool IsActive() const { return m_Active; }

		virtual void Update() = 0;
	protected:
		Ref<Scene> m_Scene;
	private:
		bool m_Active = false;
	};
}