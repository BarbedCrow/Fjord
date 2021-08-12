#include "fjordpch.h"
#include "Component.h"

namespace Fjord
{
	std::unordered_map<std::string, uint32_t> Component::s_MetaComponentsStorage = std::unordered_map<std::string, uint32_t>();

	const uint32_t Component::CREATE_FUNC = "Create"_hs;
	const uint32_t Component::GET_FUNC = "Get"_hs;
}