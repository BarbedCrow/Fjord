#pragma once

#include "Buffer.h"

namespace Fjord
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Bind() const;
		void Unbind() const;
		void SetVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) ;
		void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) ;

		const Ref<VertexBuffer>& GetVertexBuffer() const { return m_VertexBuffer; }
		const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
	private:
		uint32_t m_RendererID;
		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}

