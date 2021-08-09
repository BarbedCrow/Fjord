#pragma once

#include <yaml-cpp/yaml.h>

#include "Fjord/core/Core.h"

#include <entt/entt.hpp>

using namespace entt::literals;

namespace Fjord
{
	

	class Component
	{
	public:
		Component() = default;
		virtual ~Component() {}

		virtual void Load(YAML::Node& entt) = 0;
		virtual void Save(YAML::Emitter& out) = 0;

		template<typename Type>
		static Type& Get(entt::registry& registry, entt::entity entity) {
			return registry.get<Type>(entity);
		}

		template<typename Type>
		static Type& Create(entt::registry& registry, entt::entity entity)
		{
			return registry.emplace<Type>(entity);
		}

		template<typename Type>
		static void Register()
		{
			entt::meta<Type>().type()
				.base<Component>()
				.func<&Component::Create<Type>, entt::as_ref_t> (CREATE_FUNC)
				.func<&Component::Get<Type>, entt::as_ref_t> (GET_FUNC)
				.func<&Type::Save, entt::as_ref_t> (SAVE_FUNC)
				.func<&Type::Load, entt::as_ref_t > (LOAD_FUNC);
		}
	public:
		static const uint32_t CREATE_FUNC;
		static const uint32_t GET_FUNC;
		static const uint32_t SAVE_FUNC;
		static const uint32_t LOAD_FUNC;
	};
}