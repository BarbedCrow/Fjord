#include "fjordpch.h"
#include "SceneLoader.h"

#include <fstream>

#include <yaml-cpp/yaml.h>

#include "Fjord/ECS/Components/Components.h"

namespace Fjord
{
	bool SceneLoader::Load(const std::string& path)
	{
		YAML::Node data = YAML::LoadFile(path);
		if (!data["Scene"]) return false;

		YAML::Node entities = data["Entities"];
		if (entities)
		{
			auto registry = m_Scene->GetRegistry();
			for (YAML::Node& entity : entities)
			{
				auto entt = registry->create();

				auto components = entity["Components"];
				if (components)
				{
					for (YAML::Node& comp : components)
					{
						auto typeIdStr = comp["Component"].as<std::string>();
						entt::id_type id = std::stoul(typeIdStr.c_str());
						auto compType = entt::resolve(id);
						auto compMeta = compType.func(Component::CREATE_FUNC).invoke({}, entt::forward_as_meta(*registry), entt);
						compType.func(Component::LOAD_FUNC).invoke(compMeta, entt::forward_as_meta(comp));
					}
				}
			}
		}

		return true;
	}

	bool SceneLoader::LoadRuntime(const std::string& path)
	{
		//NOT IMPLEMENTED
		FJORD_CORE_ASSERT(false);
		return false;
	}

	void SceneLoader::Save(const std::string& path)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "Untitled";
		out << YAML::Key << "Entities" << YAML::Value;

		out << YAML::BeginSeq; //Entities

		auto view = m_Scene->GetRegistry()->view<UIDComponent>(entt::exclude<EditorComponent>);
		auto registry = m_Scene->GetRegistry();
		for (auto entt : view)
		{
			out << YAML::BeginMap;// Entity
			out << YAML::Key << "Entity" << YAML::Value << "1231232"; // add id
			
			out << YAML::Key << "Components" << YAML::Value;
			out << YAML::BeginSeq; // Components
			registry->visit(entt, [&](const auto info)
				{
					const auto type = entt::resolve(info);
					out << YAML::BeginMap;
					out << YAML::Key << "Component" << YAML::Value << type.id();
					auto any = type.func(Component::GET_FUNC).invoke({}, entt::forward_as_meta(*registry), entt);
					type.func(Component::SAVE_FUNC).invoke(any, entt::forward_as_meta(out));
					out << YAML::EndMap;
				});
			out << YAML::EndSeq; // Components

			out << YAML::EndMap;// Entity
		}

		out << YAML::EndSeq; //Entities
		out << YAML::EndMap;

		std::ofstream fout(path);
		fout << out.c_str();
	}

	void SceneLoader::SaveRuntime(const std::string& path)
	{
		//NOT IMPLEMENTED
		FJORD_CORE_ASSERT(false);
	}
	
}