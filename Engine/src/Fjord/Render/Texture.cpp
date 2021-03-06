#include "fjordpch.h"
#include "Texture.h"

#include <glad/glad.h>

#include <stb/stb_image.h>

namespace Fjord
{
	Texture2D::Texture2D(uint32_t width, uint32_t height) : m_Width(width), m_Height(height)
	{
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	Texture2D::Texture2D(const std::string& path, bool flipVert)
		: dbgPath(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(flipVert);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		FJORD_CORE_ASSERT(data, "failed to load image");

		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0;
		GLenum dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;

		FJORD_CORE_ASSERT(internalFormat, "Some unknown format");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void Texture2D::SetData(void* data, uint32_t size)
	{
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void Texture2D::Bind(uint32_t slot)
	{
		m_Slot = slot;
		glBindTextureUnit(slot, m_RendererID);
	}

	void Texture2D::Unbind()
	{
		glBindTextureUnit(m_Slot, 0);
	}

	//TEXTURE LIBRARY////////////////////////////////////////////////////////////
	Ref<Texture2D>& TextureLibrary::Get(const std::string& name)
	{
		if (!Exists(name)) Load(name);
		return m_Textures.find(name)->second;
	}

	Ref<Texture2D>& TextureLibrary::Load(const std::string& name)
	{
		auto& texture = CreateRef<Texture2D>(name);
		m_Textures[name] = texture;
		return texture;
	}
	////////////////////////////////////////////////////////////////////////////

}