#pragma once

#include "Buffer.h"

namespace Fjord
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		virtual void Bind() const;
		virtual void Unbind() const;
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) ;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) ;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
	private:
		uint32_t m_RendererID;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}

