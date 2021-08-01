#pragma once

#include <entt/entt.hpp>

namespace Fjord
{
	class GameSystem
	{
	public:
		GameSystem(entt::registry* registry, bool isActive = true) : m_Registry(registry), m_Active(isActive) {}
		virtual ~GameSystem() {}

		void Activate() { m_Active = true; }
		void Deactivate() { m_Active = false; }

		inline bool IsActive() const { return m_Active; }

		virtual void Update() = 0;
	protected:
		entt::registry* m_Registry;
	private:
		bool m_Active = false;
	};
}