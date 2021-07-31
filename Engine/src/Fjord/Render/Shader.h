#pragma once

#include <glm/glm.hpp>

typedef unsigned int GLenum;
#define MAX_SHADER_SOURCES_AMOUNT 3

namespace Fjord
{
	class Shader
	{
	public:
		Shader(const std::string& filepath);
		Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual const std::string& GetName() const { return m_Name; }

		virtual void UploadUniformInt(const std::string& name, int val);
		virtual void UploadUniformFloat(const std::string& name, float val);
		virtual void UploadUniformVec3(const std::string& name, const glm::vec3& vector);
		virtual void UploadUniformVec2(const std::string& name, const glm::vec2& vector);
		virtual void UploadUniformVec4(const std::string& name, const glm::vec4& vector);
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		std::string ReadFile(const std::string& path);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& file);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSrcs);
	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};

	class ShaderLibrary
	{
	public:
		void Add(const std::string& name, const Ref<Shader>& shader);
		void Add(const Ref<Shader>& shader);

		Ref<Shader> Get(const std::string& name);
		Ref<Shader> Load(const std::string& filepath);
		Ref<Shader> Load(const std::string& name, const std::string& filepath);

		bool Exists(const std::string& name) { return m_Shaders.find(name) != m_Shaders.end(); }
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}
