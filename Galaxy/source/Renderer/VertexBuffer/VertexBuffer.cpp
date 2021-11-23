#include "GL/glew.h"
#include "VertexBuffer.h"

namespace Galaxy 
{
	VertexBuffer::VertexBuffer()
	{
		glGenBuffers(1, &ID);
	}

	VertexBuffer* VertexBuffer::Create()
	{
		return new VertexBuffer();
	}

	void VertexBuffer::SetData(GLsizeiptr size, const void* data)
	{
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
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
