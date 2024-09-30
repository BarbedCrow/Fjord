#pragma once

#include "Fjord/Render/Texture.h"

#include <Fjord/ECS/Components/RendererComponent.h>

namespace Fjord
{
	class ModelRendererComponent : public RendererComponent
	{
	public:
		ModelRendererComponent() = default;
		ModelRendererComponent(const ModelRendererComponent&) = default;

		void OnInit() override;

		void Bind();
		void Unbind();

		const std::vector<glm::vec3>& GetVertices() const { return m_vertices; }
		std::vector<uint32_t> GetIndices() const { return m_indices; }

		const std::vector<glm::vec2>& GetUvs() const { return m_uvs; }

	protected:
		virtual void SetupProxy() override;

	private:
		TextureLibrary m_textureLibrary;

		Ref<Texture2D> m_texture;

		std::vector<glm::vec3> m_vertices;
		std::vector<uint32_t> m_indices;

		std::vector<glm::vec2> m_uvs;
		std::vector<glm::vec3> m_normals;
	};
}
