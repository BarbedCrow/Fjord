#include "fjordpch.h"
#include "SpriteRendererComponent.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "Fjord/Utils/YAMLUtils.h"

namespace Fjord
{
	SpriteRendererComponent::SpriteRendererComponent()
	{
		SetupProxy();

		Material = CreateRef <Shader>("assets/shaders/BasicShader.glsl");
	}

	void SpriteRendererComponent::SetupProxy()
	{
		m_Proxy.Name = entt::resolve<SpriteRendererComponent>().info().name();
		m_Proxy.Members.push_back(CreateRef<ComponentMemberColorRGBA>("Color", &Color));
		m_Proxy.Members.push_back(CreateRef<ComponentMemberTexture>("Texture", &Texture));
		m_Proxy.Members.push_back(CreateRef<ComponentMemberFloat>("Tiling Factor", &TilingFactor));
	}

}