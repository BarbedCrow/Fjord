#pragma once

#include <string>

#include "Component.h"

namespace Fjord
{
	class UIDComponent : public Component
	{
	public:
		UIDComponent();
		UIDComponent(const UIDComponent&) = default;
		UIDComponent(const std::string& uid) : UID(uid) {}
	public:
		std::string UID;
	protected:
		virtual void SetupProxy() override;
	};
}