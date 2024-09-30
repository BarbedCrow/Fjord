#pragma once

#include <glm/glm.hpp>

namespace Fjord
{
	class ModelLoader
	{
	public:
		static bool LoadObj(const char* path, std::vector<glm::vec3>& oVertices, std::vector<uint32_t>& oIndices, std::vector<glm::vec2>& oUvs, std::vector<glm::vec3>& oNormals);
	};
}
