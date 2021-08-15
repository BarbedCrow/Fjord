#include "fjordpch.h"
#include "VertexArray.h"

#include <glad/glad.h>

namespace Fjord
{

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Fjord::ShaderDataType::None:
			return GL_NONE;
		case Fjord::ShaderDataType::Float:
			return GL_FLOAT;
		case Fjord::ShaderDataType::Float2:
			return GL_FLOAT;
		case Fjord::ShaderDataType::Float3:
			return GL_FLOAT;
		case Fjord::ShaderDataType::Float4:
			return GL_FLOAT;
		case Fjord::ShaderDataType::Mat3:
			return GL_FLOAT;
		case Fjord::ShaderDataType::Mat4:
			return GL_FLOAT;
		case Fjord::ShaderDataType::Int:
			return GL_INT;
		case Fjord::ShaderDataType::Int2:
			return GL_INT;
		case Fjord::ShaderDataType::Int3:
			return GL_INT;
		case Fjord::ShaderDataType::Int4:
			return GL_INT;
		case Fjord::ShaderDataType::Bool:
			return GL_BOOL;
		default:
			FJORD_CORE_ERROR("Unknown ShaderDataType: {0+}", type);
			FJORD_CORE_ASSERT(false, "Unknown ShaderDataType. See above for more info");
			return GL_NONE;
		}
	}

	VertexArray::VertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void VertexArray::SetVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		FJORD_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Layout of vertex buffer is empty");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t idx = 0;
		BufferLayout layout = vertexBuffer->GetLayout();
		for (const auto& el : layout)
		{
			glEnableVertexAttribArray(idx);
			glVertexAttribPointer(idx, el.GetElementCount(), ShaderDataTypeToOpenGLBaseType(el.Type),
				el.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)el.Offset);
			idx++;
		}

		m_VertexBuffer = vertexBuffer;
	}

	void VertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}

}