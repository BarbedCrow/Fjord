#pragma once

#include <entt/entt.hpp>

#include "Fjord/ECS/Scene.h"

namespace Fjord
{
	class GameSystem
	{
	public:
		GameSystem(Ref<Scene>& scene, bool isActive = true) : m_scene(scene), m_active(isActive) {}
		virtual ~GameSystem() = default;

		virtual void Activate() { m_active = true; }
		virtual void Deactivate() { m_active = false; }

		inline bool IsActive() const { return m_active; }

		virtual void Update() = 0;
	protected:
		Ref<Scene> m_scene;
	private:
		bool m_active = false;
	};
}