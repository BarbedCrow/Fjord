#pragma once

#include <string>

#include "Component.h"

namespace Fjord
{
	class UIDComponent : public Component
	{
	public:
		std::string UID;

		UIDComponent() : Component() {}
		UIDComponent(const std::string& uid) : UID(uid) {}

		virtual void Load(YAML::Node& entt) override;
		virtual void Save(YAML::Emitter& out) override;
		virtual void EditorDisplay() override {};
	};
}