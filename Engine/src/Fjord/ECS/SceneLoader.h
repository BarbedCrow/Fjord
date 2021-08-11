#pragma once

#include <string>

#include "Fjord/core/Core.h"
#include "Fjord/ECS/Scene.h"

#include "Fjord/ECS/Components/Components.h"

namespace Fjord
{
	class SceneLoader
	{
	public:
		SceneLoader(const Ref<Scene>& scene) : m_Scene(scene) { };

		bool Load(const std::string& path);
		bool LoadRuntime(const std::string& path);

		void Save(const std::string& path);
		void SaveRuntime(const std::string& path);

	protected:
		void LoadComponent(Component* component, YAML::Node& data);
		void SaveComponent(Component* component, YAML::Emitter& out);
	private:
		Ref<Scene> m_Scene;
	};

}
