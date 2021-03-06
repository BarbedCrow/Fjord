#include "fjordpch.h"
#include "UIDComponent.h"

namespace Fjord
{
	UIDComponent::UIDComponent()
	{
		SetupProxy();
	}

	void UIDComponent::SetupProxy()
	{
		m_Proxy.Name = entt::resolve<UIDComponent>().info().name();
		m_Proxy.Members.push_back(CreateRef<ComponentMemberString>("id", &UID));
	}

}