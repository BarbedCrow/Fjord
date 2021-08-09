#include "fjordpch.h"
#include "UIDComponent.h"

namespace Fjord
{

	void UIDComponent::Load(YAML::Node& entt)
	{
		auto uidEnt = entt["id"];
		UID = uidEnt ? uidEnt.as<std::string>() : UID;
	}

	void UIDComponent::Save(YAML::Emitter& out)
	{
		out << YAML::Key << "id" << YAML::Value << UID;
	}

}