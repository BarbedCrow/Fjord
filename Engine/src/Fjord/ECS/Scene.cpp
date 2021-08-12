#include "fjordpch.h"
#include "Scene.h"

#include "Fjord/ECS/Components/Components.h"

namespace Fjord
{

	Scene::Scene()
	{

	}

	Scene::Scene(std::string path) : m_Path(path)
	{

	}

	Scene::~Scene()
	{

	}

	entt::entity& Scene::CreateEmptyEntity()
	{
		auto entity = m_Registry.create();
		m_Registry.emplace<UIDComponent>(entity, "entity");
		return entity;
	}

}