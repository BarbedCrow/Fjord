#include "fjordpch.h"
#include "UIDComponent.h"

namespace Fjord
{
	UIDComponent::UIDComponent()
	{
	}

	void UIDComponent::SetupProxy()
	{
		m_proxy.Name = entt::resolve<UIDComponent>().info().name();
		m_proxy.Members.push_back(CreateRef<ComponentMemberString>("id", &UID));
	}

}