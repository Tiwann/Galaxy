#include "IndexBuffer.h"

namespace Galaxy 
{
	IndexBuffer::IndexBuffer()
	{
		glGenBuffers(1, &ID);
	}

	IndexBuffer* IndexBuffer::Create()
	{
		return new IndexBuffer();
	}

	void IndexBuffer::SetData(GLsizeiptr size, const void* data)
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	void IndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	}

	void IndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
