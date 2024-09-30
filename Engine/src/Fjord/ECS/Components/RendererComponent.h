#pragma once

#include <Fjord/ECS/Components/Component.h>

namespace Fjord
{
	class RendererComponent : public Component
	{
	public:
		RendererComponent() {}
		RendererComponent(const RendererComponent&) = default;

	protected:
		virtual void SetupProxy() override;
	};
}
