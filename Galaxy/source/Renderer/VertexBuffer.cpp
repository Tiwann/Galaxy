#include "VertexBuffer.h"

namespace Galaxy 
{
	VertexBuffer::VertexBuffer()
	{
		glGenBuffers(1, &ID);
	}

	std::shared_ptr<VertexBuffer> VertexBuffer::Create()
	{
		return std::make_shared<VertexBuffer>(VertexBuffer());
	}

	void VertexBuffer::SetData(GLsizeiptr size, const void* data)
	{
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	void VertexBuffer::SetData(Vertices vertices)
	{
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * Galaxy::Vertex::GetSize(), vertices.data(), GL_STATIC_DRAW);
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, ID);
	}

	void VertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}
