#pragma once

#include <yaml-cpp/yaml.h>
#include <entt/entt.hpp>

#include "Fjord/core/Core.h"
#include "ComponentProxy.h"

using namespace entt::literals;

namespace Fjord
{
	class Component
	{
	public:
		Component() = default;
		virtual ~Component() {}

		// this data is used to get user possibility to define what component data
		//should be saved/loaded, shown in editor
		ComponentProxy& GetProxy() { return m_Proxy; }
		
		//Always call this method for newly added components
		//It allows entt system to register all meta data for your component so that 
		//you could create, save, load, display it without referring to particular component class
		template<typename Type>
		static void Register();

		static const std::unordered_map<std::string, uint32_t>& GetMetaComponentsStorage() { return s_MetaComponentsStorage; }
	public:
		static const uint32_t CREATE_FUNC;
		static const uint32_t GET_FUNC;
	protected:

		//USE this function to define what data you want to save/load, show in editor
		virtual void SetupProxy() = 0;
	protected:
		ComponentProxy m_Proxy;
		std::vector<ComponentMember> m_OuterData;
	private:

		//Holds meta data in format [name, hash to resolve meta info] for all registered components
		static std::unordered_map<std::string, uint32_t> s_MetaComponentsStorage;

		//DON'T use this method without necessity
		//It is used to create and emplace the component for given entity during deserialization
		template<typename Type>
		static Type& Create(entt::registry& registry, entt::entity entity);

		//DON'T use this method without necessity
		//It is used to get the component of given entity during serialization
		template<typename Type>
		static Type& Get(entt::registry& registry, entt::entity entity);
	};

	template<typename Type>
	void Component::Register()
	{
		entt::meta<Type>().type()
			.base<Component>()
			.func<&Component::Create<Type>, entt::as_ref_t>(CREATE_FUNC)
			.func<&Component::Get<Type>, entt::as_ref_t>(GET_FUNC);

		entt::type_info info = entt::resolve<Type>().info();
		std::string name = info.name().data();
		s_MetaComponentsStorage[name] = static_cast<uint32_t>(info.hash());
	}

	template<typename Type>
	Type& Component::Create(entt::registry& registry, entt::entity entity)
	{
		return registry.emplace<Type>(entity);
	}

	template<typename Type>
	Type& Component::Get(entt::registry& registry, entt::entity entity) {
		return registry.get<Type>(entity);
	}
}