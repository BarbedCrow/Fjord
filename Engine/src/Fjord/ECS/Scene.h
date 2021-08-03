#pragma once

#include <entt/entt.hpp>

namespace Fjord
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		// TO DO: consider making this method private and adding SceneLoader as a friend class
		entt::registry* GetRegistry() { return &m_Registry; } 
		const std::string GetPath() const { return m_Path; }
	private:
		std::string m_Path;
		entt::registry m_Registry;
	};
}

