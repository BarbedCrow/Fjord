#pragma once

typedef unsigned int GLenum;

namespace Fjord
{
	class Texture2D
	{
	public:
		Texture2D(const std::string& path, bool flipVert = 1);
		Texture2D(uint32_t width, uint32_t height);
		~Texture2D();

		uint32_t GetRendererID() const { return m_RendererID; }
		uint32_t GetSlot() const { return m_Slot; }

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

		void SetData(void* data, uint32_t size);

		void Bind(uint32_t slot = 0);
		void Unbind();
	private:
		uint32_t m_RendererID;
		uint32_t m_Slot = 0;
		uint32_t m_Width, m_Height;

		GLenum m_InternalFormat, m_DataFormat;

		std::string dbgPath;
	};


	//TEXTURE LIBRARY
	class TextureLibrary
	{
	public:
		Ref<Texture2D>& Get(const std::string& name);
	private:
		bool Exists(const std::string& name) { return m_Textures.find(name) != m_Textures.end(); }
		Ref<Texture2D>& Load(const std::string& name);
	private:
		std::unordered_map<std::string, Ref<Texture2D>> m_Textures;
	};
}
