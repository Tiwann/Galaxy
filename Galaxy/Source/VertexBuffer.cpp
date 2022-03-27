#include "VertexBuffer.h"

namespace Galaxy 
{
	VertexBuffer::VertexBuffer() : ID(0)
	{
		glGenBuffers(1, &ID);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &ID);
	}

	void VertexBuffer::SetData(GLsizeiptr size, const void* data)
	{
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	void VertexBuffer::SetData(const std::vector<Vertex>& vertices)
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
