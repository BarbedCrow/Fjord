#include "fjordpch.h"

#include "ModelRendererComponent.h"

#include <Fjord/Utils/ModelLoader.h>

namespace Fjord
{
	void ModelRendererComponent::OnInit()
	{
		RendererComponent::OnInit();

		// test suzanne bench
		const std::string TestModelPath = "resources/models/suzanne.obj";
		if (ModelLoader::LoadObj(TestModelPath.c_str(), m_vertices, m_indices, m_uvs, m_normals)) {
		}
		else {
		}

		m_texture = m_textureLibrary.Get("resources/models/grass.png");
	}

	void ModelRendererComponent::Bind()
	{
		if (m_texture) {
			m_texture->Bind();
		}
	}

	void ModelRendererComponent::Unbind()
	{
		if (m_texture) {
			m_texture->Unbind();
		}
	}

	void ModelRendererComponent::SetupProxy()
	{
		RendererComponent::SetupProxy();
	}
}
