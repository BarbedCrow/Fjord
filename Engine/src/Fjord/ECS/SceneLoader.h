#pragma once

#include <string>

#include "Fjord/core/Core.h"
#include "Fjord/ECS/Scene.h"

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

	private:
		Ref<Scene> m_Scene;
	};

}
