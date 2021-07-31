#include "fjordpch.h"
#include "Shader.h"

#include <fstream>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Fjord
{

	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment")
			return GL_FRAGMENT_SHADER;

		FJORD_CORE_ASSERT("Unknown shader type: {0}", type);
		return 0;
	}

	Shader::Shader(const std::string& filepath)
	{
		std::string file = ReadFile(filepath);
		if (file == "")
		{
			//TO DO: Set default shaders
			return;
		}

		Compile(PreProcess(file));

		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind('.');
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		m_Name = filepath.substr(lastSlash, count);
	}

	Shader::Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		std::unordered_map<GLenum, std::string> map;
		map[GL_VERTEX_SHADER] = vertexSrc;
		map[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(map);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	void Shader::UploadUniformInt(const std::string& name, int val)
	{
		uint32_t uniformLocation = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(uniformLocation, val);
	}

	void Shader::UploadUniformFloat(const std::string& name, float val)
	{
		uint32_t uniformLocation = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(uniformLocation, val);
	}

	void Shader::UploadUniformVec2(const std::string& name, const glm::vec2& vector)
	{
		uint32_t uniformLocation = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2fv(uniformLocation, 1, glm::value_ptr(vector));
	}

	void Shader::UploadUniformVec3(const std::string& name, const glm::vec3& vector)
	{
		uint32_t uniformLocation = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3fv(uniformLocation, 1, glm::value_ptr(vector));
	}

	void Shader::UploadUniformVec4(const std::string& name, const glm::vec4& vector)
	{
		uint32_t uniformLocation = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4fv(uniformLocation, 1, glm::value_ptr(vector));
	}

	void Shader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		uint32_t uniformLocation = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	std::string Shader::ReadFile(const std::string& path)
	{
		std::string result;
		std::ifstream in(path, std::ios::in | std::ios::binary);
		if (!in)
		{
			FJORD_CORE_ERROR("Failed to find shader: {0}", path);
			return "";
		}

		in.seekg(0, std::ios::end);
		result.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&result[0], result.size());
		in.close();
		return result;
	}

	std::unordered_map<GLenum, std::string> Shader::PreProcess(const std::string& file)
	{
		std::unordered_map<GLenum, std::string> map;
		const char* typeToken = "#type";
		size_t typeTokenLen = strlen(typeToken);
		size_t pos = file.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = file.find_first_of("\r\n", pos);
			FJORD_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLen + 1;
			std::string type = file.substr(begin, eol - begin);
			size_t nextLinePos = file.find_first_not_of("\r\n", eol);
			pos = file.find(typeToken, nextLinePos);
			map[ShaderTypeFromString(type)] = file.substr(nextLinePos,
				pos - (nextLinePos == std::string::npos ? file.size() - 1 : nextLinePos));
		}
		return map;
	}

	void Shader::Compile(const std::unordered_map<GLenum, std::string>& shaderSrcs)
	{
		GLuint program = glCreateProgram();
		FJORD_CORE_ASSERT(shaderSrcs.size() <= MAX_SHADER_SOURCES_AMOUNT, "There are more than {0} shader sources to compile", MAX_SHADER_SOURCES_AMOUNT);
		std::array<GLenum, MAX_SHADER_SOURCES_AMOUNT> glShaderIds;
		int glShaderId = 0;
		for (auto& kv : shaderSrcs)
		{
			GLenum type = kv.first;
			const std::string& source = kv.second;

			GLuint shader = glCreateShader(type);

			const GLchar* sourceCstr = source.c_str();
			glShaderSource(shader, 1, &sourceCstr, 0);
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				FJORD_CORE_ERROR(" {0}", infoLog.data());
				FJORD_CORE_ASSERT(false, "{0} shader compilation error!", type);
				return;
			}

			glShaderIds[glShaderId++] = shader;
			glAttachShader(program, shader);
		}

		m_RendererID = program;
		glLinkProgram(m_RendererID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			if (infoLog.size() > 0)
			{
				glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);
			}

			// We don't need the program anymore.
			glDeleteProgram(m_RendererID);
			// Don't leak shaders either.
			for (auto id : glShaderIds)
			{
				glDeleteShader(id);
			}

			FJORD_CORE_ERROR(" {0}", infoLog.data());
			FJORD_CORE_ASSERT(false, "Shader link error!");
			return;
		}

		// Always detach shaders after a successful link.
		for (auto id : glShaderIds)
		{
			glDetachShader(m_RendererID, id);
		}
	}

}