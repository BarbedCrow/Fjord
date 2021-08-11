#pragma once

#include "Component.h"

namespace Fjord
{
	class EditorComponent : public Component
	{
	public:
		EditorComponent() = default;
	protected:
		virtual void SetupProxy() override {}
	};
}