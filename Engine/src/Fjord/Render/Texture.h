#pragma once

typedef unsigned int GLenum;

namespace Fjord
{
	class Texture2D
	{
	public:
		Texture2D(const std::string& path);
		Texture2D(uint32_t width, uint32_t height);
		~Texture2D();

		uint32_t GetRendererID() const { return m_RendererID; }

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

		void SetData(void* data, uint32_t size);

		void Bind(uint32_t slot = 0) const;
	private:
		uint32_t m_RendererID;

		uint32_t m_Width, m_Height;

		GLenum m_InternalFormat, m_DataFormat;

		std::string dbgPath;
	};
}
