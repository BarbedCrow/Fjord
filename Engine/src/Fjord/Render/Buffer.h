#pragma once

#include <string>
#include <vector>

#include "Fjord/core/Core.h"
#include "Fjord/core/Log.h"

namespace Fjord
{

	enum class ShaderDataType
	{
		None = 0,
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
		Int, Int2, Int3, Int4,
		Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case Fjord::ShaderDataType::None:
			return 0;
		case Fjord::ShaderDataType::Float:
			return 4;
		case Fjord::ShaderDataType::Float2:
			return 4 * 2;
		case Fjord::ShaderDataType::Float3:
			return 4 * 3;
		case Fjord::ShaderDataType::Float4:
			return 4 * 4;
		case Fjord::ShaderDataType::Mat3:
			return 4 * 3 * 3;
		case Fjord::ShaderDataType::Mat4:
			return 4 * 3 * 4;
		case Fjord::ShaderDataType::Int:
			return 4;
		case Fjord::ShaderDataType::Int2:
			return 4 * 2;
		case Fjord::ShaderDataType::Int3:
			return 4 * 3;
		case Fjord::ShaderDataType::Int4:
			return 4 * 4;
		case Fjord::ShaderDataType::Bool:
			return 1;
		default:
			FJORD_CORE_ASSERT(false, "Unknown ShaderDataType {0}", (int)type);
			return 0;
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//BUFFER LAYOUT///////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		BufferElement() {}

		BufferElement(ShaderDataType type, const std::string name, bool normalized = false)
			:
			Name(name),
			Type(type),
			Size(ShaderDataTypeSize(type)),
			Offset(0),
			Normalized(normalized)
		{}

		uint32_t GetElementCount() const
		{
			switch (Type)
			{
			case Fjord::ShaderDataType::None:
				return 0;
			case Fjord::ShaderDataType::Float:
				return 1;
			case Fjord::ShaderDataType::Float2:
				return 2;
			case Fjord::ShaderDataType::Float3:
				return 3;
			case Fjord::ShaderDataType::Float4:
				return 4;
			case Fjord::ShaderDataType::Mat3:
				return 3 * 3;
			case Fjord::ShaderDataType::Mat4:
				return 4 * 4;
			case Fjord::ShaderDataType::Int:
				return 1;
			case Fjord::ShaderDataType::Int2:
				return 2;
			case Fjord::ShaderDataType::Int3:
				return 3;
			case Fjord::ShaderDataType::Int4:
				return 4;
			case Fjord::ShaderDataType::Bool:
				return 1;
			}
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& elements);

		inline const std::vector<BufferElement> GetElements() const { return m_Elements; }
		inline const uint32_t GetStride() const { return m_Stride; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		void CalculateOffsetsAndStride();
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//VERTEX BUFFER///////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	class VertexBuffer
	{
	public:
		VertexBuffer(uint32_t size);
		VertexBuffer(float* vertices, uint32_t size);
		~VertexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;
		virtual void SetLayout(const BufferLayout& layout) { m_Layout = layout; }
		virtual const BufferLayout& GetLayout() const { return m_Layout; }
	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//INDEX BUFFER////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	class IndexBuffer
	{
	public:
		IndexBuffer(uint32_t* indices, uint32_t count);
		~IndexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual uint32_t GetCount() const { return m_Count; }
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};

}