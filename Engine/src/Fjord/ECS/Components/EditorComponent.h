#pragma once

#include "Component.h"

namespace Fjord
{
	class EditorComponent : public Component
	{
	public:
		EditorComponent() : Component() {}

		virtual void Load(YAML::Node& entt) override {}
		virtual void Save(YAML::Emitter& out) override {}
		virtual void EditorDisplay() override {}

	};
}