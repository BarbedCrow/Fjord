#pragma once

#include <entt/entt.hpp>

namespace Fjord
{
	class Scene
	{
	public:
		Scene();
		Scene(std::string path);
		~Scene();

		Scene& operator =(Scene& other)
		{
			std::swap(m_Path, other.m_Path);
			std::swap(m_Registry, other.m_Registry);
			return *this;
		}

		entt::entity CreateEmptyEntity();
		template<typename Component, typename... Args>
		decltype(auto) CreateComponent(const entt::entity entity, Args &&... args);

		// TO DO: consider making this method private and adding SceneLoader as a friend class
		entt::registry* const GetRegistry() { return &m_Registry; } 
		const std::string GetPath() const { return m_Path; }

		entt::registry m_Registry;
	private:
		std::string m_Path;
		
	};

	template<typename Component, typename... Args>
	decltype(auto) Scene::CreateComponent(const entt::entity entity, Args &&... args)
	{
		auto& component = m_Registry.emplace<Component>(entity, std::forward<Args>(args)...);
		component.Init();
		return component;
	}
}

